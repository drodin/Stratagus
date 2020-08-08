R"(
// VHS shader
// by hunterk
// adapted from ompuco's more AVdistortion shadertoy:
// https://www.shadertoy.com/view/XlsczN

// Parameter lines go here:
#pragma parameter wiggle Wiggle 0.0 0.0 10.0 1.0
#pragma parameter smear ChromaSmear 0.5 0.0 1.0 0.05

#if defined(VERTEX)

#if __VERSION__ >= 130
#define COMPAT_VARYING out
#define COMPAT_ATTRIBUTE in
#define COMPAT_TEXTURE texture
#else
#define COMPAT_VARYING varying
#define COMPAT_ATTRIBUTE attribute
#define COMPAT_TEXTURE texture2D
#endif

#ifdef GL_ES
#define COMPAT_PRECISION mediump
#else
#define COMPAT_PRECISION
#endif

COMPAT_ATTRIBUTE vec4 VertexCoord;
COMPAT_ATTRIBUTE vec4 COLOR;
COMPAT_ATTRIBUTE vec4 TexCoord;
COMPAT_VARYING vec4 COL0;
COMPAT_VARYING vec4 TEX0;

vec4 _oPosition1;
uniform mat4 MVPMatrix;
uniform COMPAT_PRECISION int FrameDirection;
uniform COMPAT_PRECISION int FrameCount;
uniform COMPAT_PRECISION vec2 OutputSize;
uniform COMPAT_PRECISION vec2 TextureSize;
uniform COMPAT_PRECISION vec2 InputSize;

// compatibility #defines
#define vTexCoord TEX0.xy
#define SourceSize vec4(TextureSize, 1.0 / TextureSize) //either TextureSize or InputSize
#define OutSize vec4(OutputSize, 1.0 / OutputSize)

void main()
{
    gl_Position = MVPMatrix * VertexCoord;
    TEX0.xy = TexCoord.xy;
}

#elif defined(FRAGMENT)

#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
#define COMPAT_PRECISION mediump
#else
#define COMPAT_PRECISION
#endif

#if __VERSION__ >= 130
#define COMPAT_VARYING in
#define COMPAT_TEXTURE texture
out COMPAT_PRECISION vec4 FragColor;
#else
#define COMPAT_VARYING varying
#define FragColor gl_FragColor
#define COMPAT_TEXTURE texture2D
#endif

uniform COMPAT_PRECISION int FrameDirection;
uniform COMPAT_PRECISION int FrameCount;
uniform COMPAT_PRECISION vec2 OutputSize;
uniform COMPAT_PRECISION vec2 TextureSize;
uniform COMPAT_PRECISION vec2 InputSize;
uniform sampler2D Texture;
uniform sampler2D play;
COMPAT_VARYING vec4 TEX0;

// compatibility #defines
#define Source Texture
#define vTexCoord TEX0.xy

#define SourceSize vec4(TextureSize, 1.0 / TextureSize) //either TextureSize or InputSize
#define OutSize vec4(OutputSize, 1.0 / OutputSize)

#ifdef PARAMETER_UNIFORM
uniform COMPAT_PRECISION float wiggle;
uniform COMPAT_PRECISION float smear;
#else
#define wiggle 3.0
#define smear 0.5
#endif

#define iTime mod(float(FrameCount), 7.0)
#define iChannel0 Texture

//YIQ/RGB shit
vec3 rgb2yiq(vec3 c){
					return vec3(
						(0.2989*c.x + 0.5959*c.y + 0.2115*c.z),
						(0.5870*c.x - 0.2744*c.y - 0.5229*c.z),
						(0.1140*c.x - 0.3216*c.y + 0.3114*c.z)
					);
				}

vec3 yiq2rgb(vec3 c){
					return vec3(
						(	 1.0*c.x +	  1.0*c.y + 	1.0*c.z),
						( 0.956*c.x - 0.2720*c.y - 1.1060*c.z),
						(0.6210*c.x - 0.6474*c.y + 1.7046*c.z)
					);
				}

vec2 Circle(float Start, float Points, float Point)
{
	float Rad = (3.141592 * 2.0 * (1.0 / Points)) * (Point + Start);
	//return vec2(sin(Rad), cos(Rad));
		return vec2(-(.3+Rad), cos(Rad));

}

vec3 Blur(vec2 uv, float d){
	float t = (sin(iTime*5.0+uv.y*5.0))/10.0;
    float b = 1.0;
    t=0.0;
    vec2 PixelOffset=vec2(d+.0005*t,0);

    float Start = 2.0 / 14.0;
    vec2 Scale = 0.66 * 4.0 * 2.0 * PixelOffset.xy;

    vec3 N0 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 0.0) * Scale).rgb;
    vec3 N1 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 1.0) * Scale).rgb;
    vec3 N2 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 2.0) * Scale).rgb;
    vec3 N3 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 3.0) * Scale).rgb;
    vec3 N4 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 4.0) * Scale).rgb;
    vec3 N5 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 5.0) * Scale).rgb;
    vec3 N6 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 6.0) * Scale).rgb;
    vec3 N7 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 7.0) * Scale).rgb;
    vec3 N8 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 8.0) * Scale).rgb;
    vec3 N9 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 9.0) * Scale).rgb;
    vec3 N10 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 10.0) * Scale).rgb;
    vec3 N11 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 11.0) * Scale).rgb;
    vec3 N12 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 12.0) * Scale).rgb;
    vec3 N13 = COMPAT_TEXTURE(iChannel0, uv + Circle(Start, 14.0, 13.0) * Scale).rgb;
    vec3 N14 = COMPAT_TEXTURE(iChannel0, uv).rgb;

	vec4 clr = COMPAT_TEXTURE(iChannel0, uv);
    float W = 1.0 / 15.0;

    clr.rgb=
		(N0 * W) +
		(N1 * W) +
		(N2 * W) +
		(N3 * W) +
		(N4 * W) +
		(N5 * W) +
		(N6 * W) +
		(N7 * W) +
		(N8 * W) +
		(N9 * W) +
		(N10 * W) +
		(N11 * W) +
		(N12 * W) +
		(N13 * W) +
		(N14 * W);
    return  vec3(clr.xyz)*b;
}

float onOff(float a, float b, float c, float framecount)
{
	return step(c, sin((framecount * 0.001) + a*cos((framecount * 0.001)*b)));
}

vec2 jumpy(vec2 uv, float framecount)
{
	vec2 look = uv;
	float window = 1./(1.+80.*(look.y-mod(framecount/4.,1.))*(look.y-mod(framecount/4.,1.)));
	look.x += 0.05 * sin(look.y*10. + framecount)/20.*onOff(4.,4.,.3, framecount)*(0.5+cos(framecount*20.))*window;
	float vShift = (0.1*wiggle) * 0.4*onOff(2.,3.,.9, framecount)*(sin(framecount)*sin(framecount*20.) +
										 (0.5 + 0.1*sin(framecount*200.)*cos(framecount)));
	look.y = mod(look.y - 0.01 * vShift, 1.);
	return look;
}

void main()
{
    float timer = (float(FrameDirection) > 0.5) ? float(FrameCount) : 0.0;
	float d = 0.1 - ceil(mod(iTime/3.0,1.0) + 0.5) * 0.1;
	vec2 uv = jumpy(vTexCoord.xy, iTime);
	vec2 uv2 = uv;

    float s = 0.0001 * -d + 0.0001 * wiggle * sin(iTime);

	float e = min(.30,pow(max(0.0,cos(uv.y*4.0+.3)-.75)*(s+0.5)*1.0,3.0))*25.0;
    float r = (iTime*(2.0*s));
    uv.x+=abs(r*pow(min(.003,(-uv.y+(.01*mod(iTime, 17.0))))*3.0,2.0));

    d=.051+abs(sin(s/4.0));
    float c = max(0.0001,.002*d) * smear;
	vec2 uvo = uv;
    vec4 final;
	final.xyz =Blur(uv,c+c*(uv.x));
    float y = rgb2yiq(final.xyz).r;

	uv.x+=.01*d;
    c*=6.0;
    final.xyz =Blur(uv,c);
    float i = rgb2yiq(final.xyz).g;

    uv.x+=.005*d;

    c*=2.50;
    final.xyz =Blur(uv,c);
    float q = rgb2yiq(final.xyz).b;
	final = vec4(yiq2rgb(vec3(y,i,q))-pow(s+e*2.0,3.0), 1.0);

	vec4 play_osd = COMPAT_TEXTURE(play, uv2 * TextureSize.xy / InputSize.xy);
	float show_overlay = (mod(timer, 100.0) < 50.0) && (timer != 0.0) && (timer < 500.0) ? play_osd.a : 0.0;
	show_overlay = clamp(show_overlay, 0.0, 1.0);
	final = mix(final, play_osd, show_overlay);

    FragColor = final;
}
#endif
)"
