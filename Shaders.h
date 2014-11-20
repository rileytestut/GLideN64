#define SHADER_PRECISION

static const char* vertex_shader =
#ifdef SHADER_PRECISION
"#version 330 core										\n"
"in highp vec4 aPosition;						\n"
"in lowp vec4 aColor;							\n"
"in highp vec2 aTexCoord0;						\n"
"in highp vec2 aTexCoord1;						\n"
"in lowp float aNumLights;						\n"
"														\n"
"uniform int uRenderState;								\n"
"uniform int uTexturePersp;								\n"
"uniform lowp float uNoiseTime;							\n"
"														\n"
"uniform int uFogMode;									\n"
"uniform lowp int uFogUsage;							\n"
"uniform lowp vec4 uFogColor;							\n"
"uniform mediump float uFogMultiplier, uFogOffset;		\n"
"uniform mediump float uScreenWidth, uScreenHeight;		\n"
"														\n"
"uniform mediump vec2 uTexScale;						\n"
"uniform mediump vec2 uTexOffset[2];					\n"
"uniform mediump vec2 uTexMask[2];						\n"
"uniform mediump vec2 uCacheShiftScale[2];				\n"
"uniform mediump vec2 uCacheScale[2];					\n"
"uniform mediump vec2 uCacheOffset[2];					\n"
"uniform lowp ivec2 uCacheFrameBuffer;					\n"
"														\n"
"out lowp vec4 vShadeColor;							\n"
"out mediump vec2 vTexCoord0;						\n"
"out mediump vec2 vTexCoord1;						\n"
"out mediump vec2 vLodTexCoord;						\n"
"out mediump vec2 vNoiseCoord2D;					\n"
"out lowp float vNumLights;							\n"
"out mediump float vFogFragCoord;					\n"
#else
"in vec4	aPosition;								\n"
"in vec4	aColor;									\n"
"in vec2	aTexCoord0;								\n"
"in vec2	aTexCoord1;								\n"
"in float aNumLights;							\n"
"														\n"
"uniform int uRenderState;								\n"
"uniform int uTexturePersp;								\n"
"uniform float uNoiseTime;								\n"
"														\n"
"uniform int uFogMode;									\n"
"uniform int uFogUsage;									\n"
"uniform vec4 uFogColor;								\n"
"uniform float uFogMultiplier, uFogOffset;				\n"
"uniform float uScreenWidth, uScreenHeight;				\n"
"														\n"
"uniform vec2 	uTexScale;								\n"
"uniform vec2 	uTexOffset[2];							\n"
"uniform vec2 	uTexMask[2];							\n"
"uniform vec2 	uCacheShiftScale[2];					\n"
"uniform vec2 	uCacheScale[2];							\n"
"uniform vec2	uCacheOffset[2];						\n"
"uniform ivec2	uCacheFrameBuffer;						\n"
"														\n"
"out vec4 vShadeColor;								\n"
"out vec2 vTexCoord0;								\n"
"out vec2 vTexCoord1;								\n"
"out vec2 vLodTexCoord;								\n"
"out vec2 vNoiseCoord2D;							\n"
"out float vNumLights;								\n"
"out float vFogFragCoord;							\n"
#endif
"void main()													\n"
"{																\n"
"  gl_Position = aPosition;										\n"
"  vShadeColor = aColor;										\n"
"  if (uRenderState == 1) {										\n"
"    vec2 texCoord = aTexCoord0;								\n"
"    texCoord *= uTexScale;										\n"
"    if (uTexturePersp == 0) texCoord *= 0.5;					\n"
"    vec2 texCoord0 = texCoord*uCacheShiftScale[0];				\n"
"    if (uCacheFrameBuffer[0] != 0) {							\n"
"      if (uTexMask[0] != vec2(0.0, 0.0))						\n"
"        texCoord0 -= mod(uTexOffset[0], uTexMask[0]);			\n"
"      else														\n"
"        texCoord0 -= uTexOffset[0];							\n"
"      texCoord0.t = -texCoord0.t;								\n"
"    } else														\n"
"        texCoord0 -= uTexOffset[0];							\n"
"    vTexCoord0 = (uCacheOffset[0] + texCoord0)* uCacheScale[0];\n"
"    vec2 texCoord1 = texCoord*uCacheShiftScale[1];				\n"
"    if (uCacheFrameBuffer[1] != 0) {							\n"
"      if (uTexMask[1] != vec2(0.0, 0.0))						\n"
"        texCoord1 -= mod(uTexOffset[1], uTexMask[1]);			\n"
"      else														\n"
"        texCoord1 -= uTexOffset[1];							\n"
"      texCoord1.t = -texCoord1.t;								\n"
"    } else														\n"
"        texCoord1 -= uTexOffset[1];							\n"
"    vTexCoord1 = (uCacheOffset[1] + texCoord1)* uCacheScale[1];\n"
"    vLodTexCoord = texCoord * uCacheShiftScale[0];				\n"
"    vNumLights = aNumLights;									\n"
"  } else {														\n"
"    vTexCoord0 = aTexCoord0;									\n"
"    vTexCoord1 = aTexCoord1;									\n"
"    vNumLights = 0.0;											\n"
"  }															\n"
"  vNoiseCoord2D = vec2(gl_Position.x*uScreenWidth, gl_Position.y*uScreenHeight + uNoiseTime);\n"
"  vFogFragCoord = 0.0;											\n"
"  switch (uFogMode) {											\n"
"    case 0:													\n"
"      if (aPosition.z < -aPosition.w)							\n"
"        vFogFragCoord = -uFogMultiplier + uFogOffset;			\n"
"      else														\n"
"        vFogFragCoord = aPosition.z/aPosition.w*uFogMultiplier \n"
"	                   + uFogOffset;							\n"
"    break;														\n"
"    case 1:													\n"
"        vFogFragCoord = uFogColor.a;							\n"
"    break;														\n"
"    case 2:													\n"
"        vFogFragCoord = 1.0 - uFogColor.a;						\n"
"    break;														\n"
"  }															\n"
"  vFogFragCoord = clamp(vFogFragCoord, 0.0, 1.0);				\n"
"  if (uFogUsage == 1 && uFogMode == 0)							\n"
"     vShadeColor.a = vFogFragCoord;							\n"
"}																\n"
;

static const char* fragment_shader_header_common_variables =
#ifdef SHADER_PRECISION
"#version 330 core				\n"
"uniform sampler2D uTex0;		\n"
"uniform sampler2D uTex1;		\n"
"uniform lowp vec4 uPrimColor;	\n"
"uniform lowp vec4 uEnvColor;	\n"
"uniform lowp vec4 uCenterColor;\n"
"uniform lowp vec4 uScaleColor;	\n"
"uniform lowp vec4 uFogColor;	\n"
"uniform lowp float uK4;		\n"
"uniform lowp float uK5;		\n"
"uniform lowp float uPrimLod;	\n"
"uniform lowp int uAlphaCompareMode;	\n"
"uniform lowp int uAlphaDitherMode;	\n"
"uniform lowp int uColorDitherMode;	\n"
"uniform lowp int uGammaCorrectionEnabled;	\n"
"uniform lowp int uFogUsage;	\n"
"uniform lowp int uFb8Bit;		\n"
"uniform lowp int uFbFixedAlpha;\n"
"in lowp vec4 vShadeColor;	\n"
"in mediump vec2 vTexCoord0;\n"
"in mediump vec2 vTexCoord1;\n"
"in mediump vec2 vLodTexCoord;\n"
"in mediump vec2 vNoiseCoord2D;\n"
"in lowp float vNumLights;	\n"
"in mediump float vFogFragCoord;\n"
"lowp vec3 input_color;			\n"
"out lowp vec4 fragColor;		\n"
#else
"uniform sampler2D uTex0;		\n"
"uniform sampler2D uTex1;		\n"
"uniform vec4 uPrimColor;		\n"
"uniform vec4 uEnvColor;		\n"
"uniform vec4 uCenterColor;		\n"
"uniform vec4 uScaleColor;		\n"
"uniform vec4 uFogColor;		\n"
"uniform float uK4;				\n"
"uniform float uK5;				\n"
"uniform float uPrimLod;		\n"
"uniform int uAlphaCompareMode;	\n"
"uniform int uAlphaDitherMode;	\n"
"uniform int uColorDitherMode;	\n"
"uniform int uGammaCorrectionEnabled;\n"
"uniform int uFogUsage;		\n"
"uniform int uFb8Bit;		\n"
"uniform int uFbFixedAlpha;	\n"
"in vec4 vShadeColor;		\n"
"in vec2 vTexCoord0;		\n"
"in vec2 vTexCoord1;		\n"
"in vec2 vLodTexCoord;		\n"
"in vec2 vNoiseCoord2D;		\n"
"in float vNumLights;		\n"
"in float vFogFragCoord;	\n"
"vec3 input_color;			\n"
"out vec4 fragColor;		\n"
#endif
;

static const char* fragment_shader_header_common_functions =
#ifdef SHADER_PRECISION
"															\n"
"lowp float snoise(in mediump vec2 v);						\n"
"mediump float calc_light(in lowp int nLights, in lowp vec3 input_color, out lowp vec3 output_color);\n"
"mediump float mipmap(out lowp vec4 readtex0, out lowp vec4 readtex1);		\n"
"lowp bool depth_compare();										\n"
"lowp bool alpha_test(in lowp float alphaValue);						\n"
#else
"															\n"
"float snoise(in vec2 v);										\n"
"float calc_light(in int nLights, in vec3 input_color, out vec3 output_color);\n"
"float mipmap(out vec4 readtex0, out vec4 readtex1);		\n"
"bool depth_compare();										\n"
"bool alpha_test(in float alphaValue);						\n"
#endif
#ifdef USE_TOONIFY
"void toonify(in mediump float intensity);	\n"
#endif
;

static const char* fragment_shader_calc_light =
#ifdef SHADER_PRECISION
"#version 330 core						\n"
"uniform mediump vec3 uLightDirection[8];	\n"
"uniform lowp vec3 uLightColor[8];	\n"
"																\n"
"mediump float calc_light(in lowp int nLights, in lowp vec3 input_color, out lowp vec3 output_color) {\n"
"  output_color = input_color;									\n"
"  if (nLights == 0)											\n"
"     return 1.0;												\n"
"  mediump float full_intensity = 0.0;							\n"
"  output_color = uLightColor[nLights];							\n"
"  lowp vec3 lightColor;										\n"
"  mediump float intensity;										\n"
"  mediump vec3 n = normalize(input_color);						\n"
"  for (int i = 0; i < nLights; i++)	{						\n"
"    intensity = max(dot(n, uLightDirection[i]), 0.0);			\n"
"    full_intensity += intensity;								\n"
"    lightColor = intensity*uLightColor[i];						\n"
"    output_color += lightColor;								\n"
"  };															\n"
"  return full_intensity;										\n"
"}																\n"
#else
"uniform vec3 uLightDirection[8];	\n"
"uniform vec3 uLightColor[8];	\n"
"																\n"
"float calc_light(in int nLights, in vec3 input_color, out vec3 output_color) {\n"
"  output_color = input_color;									\n"
"  if (nLights == 0)											\n"
"     return 1.0;												\n"
"  float full_intensity = 0.0;									\n"
"  output_color = uLightColor[nLights];							\n"
"  vec3 lightColor;												\n"
"  float intensity;												\n"
"  vec3 n = normalize(input_color);								\n"
"  for (int i = 0; i < nLights; i++)	{						\n"
"    intensity = max(dot(n, uLightDirection[i]), 0.0);			\n"
"    full_intensity += intensity;								\n"
"    lightColor = intensity*uLightColor[i];						\n"
"    output_color += lightColor;								\n"
"  };															\n"
"  return full_intensity;										\n"
"}																\n"
#endif
;

static const char* alpha_test_fragment_shader =
#ifdef SHADER_PRECISION
"#version 330 core								\n"
"uniform lowp int uEnableAlphaTest;				\n"
"uniform lowp float uAlphaTestValue;			\n"
"lowp bool alpha_test(in lowp float alphaValue)	\n"
#else
"uniform int uEnableAlphaTest;				\n"
"uniform float uAlphaTestValue;				\n"
"bool alpha_test(in float alphaValue)		\n"
#endif
"{											\n"
"  if (uEnableAlphaTest == 0) return true;	\n"
"  if (uAlphaTestValue > 0.0) return alphaValue >= uAlphaTestValue;\n"
"  return alphaValue > 0.0;					\n"
"}											\n"
;

static const char* fragment_shader_header_main =
#ifdef SHADER_PRECISION
"									\n"
"void main()						\n"
"{									\n"
"  if (uAlphaCompareMode == 3) {//dither \n"
"    if (snoise(vNoiseCoord2D) < 0.0) discard; \n"
"  }								\n"
"  lowp vec4 vec_color, combined_color;	\n"
"  lowp float alpha1, alpha2;			\n"
"  lowp vec3 color1, color2;				\n"
;
#else
"									\n"
"void main()						\n"
"{									\n"
"  if (uAlphaCompareMode == 3) {//dither \n"
"    if (snoise(vNoiseCoord2D) < 0.0) discard; \n"
"  }								\n"
"  vec4 vec_color, combined_color;	\n"
"  float alpha1, alpha2;			\n"
"  vec3 color1, color2;				\n"
;
#endif

static const char* fragment_shader_color_dither =
"  if (uColorDitherMode == 2) {								\n"
"    color2 += 0.03125*snoise(vNoiseCoord2D);				\n"
"    color2 = clamp(color2, 0.0, 1.0);						\n"
"  }														\n"
;

static const char* fragment_shader_alpha_dither =
"  if (uAlphaDitherMode == 2) {								\n"
"    alpha2 += 0.03125*snoise(vNoiseCoord2D);				\n"
"    alpha2 = clamp(alpha2, 0.0, 1.0);						\n"
"  }														\n"
;

#ifdef USE_TOONIFY
static const char* fragment_shader_toonify =
"																	\n"
"void toonify(in mediump float intensity) {							\n"
"   if (intensity > 0.5)											\n"
"	   return;														\n"
"	else if (intensity > 0.125)										\n"
"		fragColor = vec4(vec3(fragColor)*0.5, fragColor.a);\n"
"	else															\n"
"		fragColor = vec4(vec3(fragColor)*0.2, fragColor.a);\n"
"}																	\n"
;
#endif

#ifdef SHADER_PRECISION
static const char* fragment_shader_readtex0color =
"  lowp vec4 readtex0 = texture(uTex0, vTexCoord0);						\n"
"  if (uFb8Bit == 1 || uFb8Bit == 3) readtex0 = vec4(readtex0.r);	\n"
"  if (uFbFixedAlpha == 1 || uFbFixedAlpha == 3) readtex0.a = 0.825;	\n"
;

static const char* fragment_shader_readtex1color =
"  lowp vec4 readtex1 = texture(uTex1, vTexCoord1);	\n"
"  if (uFb8Bit == 2 || uFb8Bit == 3) readtex1 = vec4(readtex1.r);	\n"
"  if (uFbFixedAlpha == 2 || uFbFixedAlpha == 3) readtex1.a = 0.825;	\n"
;

static const char* fragment_shader_end =
"}                               \n"
#else
static const char* fragment_shader_readtex0color =
"  vec4 readtex0 = texture(uTex0, vTexCoord0);						\n"
"  if (uFb8Bit == 1 || uFb8Bit == 3) readtex0 = vec4(readtex0.r);	\n"
"  if (uFbFixedAlpha == 1 || uFbFixedAlpha == 3) readtex0.a = 0.825;	\n"
;

static const char* fragment_shader_readtex1color =
"  vec4 readtex1 = texture(uTex1, vTexCoord1);	\n"
"  if (uFb8Bit == 2 || uFb8Bit == 3) readtex1 = vec4(readtex1.r);	\n"
"  if (uFbFixedAlpha == 2 || uFbFixedAlpha == 3) readtex1.a = 0.825;	\n"
;

static const char* fragment_shader_end =
"}                               \n"
#endif
;

static const char* fragment_shader_mipmap =
#ifdef SHADER_PRECISION
"#version 330 core					\n"
"in mediump vec2 vTexCoord0;	\n"
"in mediump vec2 vTexCoord1;	\n"
"in mediump vec2 vLodTexCoord;	\n"
"uniform sampler2D uTex0;			\n"
"uniform sampler2D uTex1;			\n"
"uniform lowp float uPrimLod;		\n"
"uniform lowp int uEnableLod;		\n"
"uniform mediump float uLodXScale;	\n"
"uniform mediump float uLodYScale;	\n"
"uniform mediump float uMinLod;		\n"
"uniform lowp int uMaxTile;			\n"
"uniform lowp int uTextureDetail;	\n"
"														\n"
"mediump float mipmap(out lowp vec4 readtex0, out lowp vec4 readtex1) {	\n"
"  if (uEnableLod == 0) {								\n"
"    readtex0 = texture(uTex0, vTexCoord0);			\n"
"    readtex1 = texture(uTex1, vTexCoord1);			\n"
"    return uPrimLod;									\n"
"  }													\n"
"  mediump vec2 dx = dFdx(vLodTexCoord);				\n"
"  dx.x *= uLodXScale;									\n"
"  dx.y *= uLodYScale;									\n"
"  mediump vec2 dy = dFdy(vLodTexCoord);				\n"
"  dy.x *= uLodXScale;									\n"
"  dy.y *= uLodYScale;									\n"
"  mediump float lod = max(length(dx), length(dy));		\n"
//" float lod = max(length(dx), length(dy)) * max(uLodXScale, uLodYScale);\n"
"  mediump float lod_tile, lod_frac;					\n"
"  lowp bool magnifying;								\n"
"  if (lod < 1.0) {										\n"
"    magnifying = true;									\n"
"    lod_tile = 0.0;									\n"
"    lod_frac = lod;									\n"
"    if (uTextureDetail != 0)							\n"
"      lod_frac = max(lod, uMinLod);					\n"
"    if (uTextureDetail == 1)							\n"
"      lod_frac = 1.0 - lod_frac;						\n"
"  } else {												\n"
"    magnifying = false;								\n"
"    lod_tile = min(float(uMaxTile), floor(log2(floor(lod)))); \n"
"    lod_frac = fract(lod/pow(2.0, lod_tile));			\n"
"  }													\n"
"  if (lod_tile < 1.0) {								\n"
"    if (magnifying) {									\n"
"      readtex0 = texture(uTex0, vTexCoord0);			\n"
//     !sharpen && !detail
"      if (uTextureDetail == 0) readtex1 = readtex0;	\n"
"      else readtex1 = texture(uTex1, vTexCoord1);	\n"
"    } else {											\n"
//     detail
"      if (uTextureDetail == 2) {						\n"
"        readtex0 = textureLod(uTex1, vTexCoord1, 0.0);\n"
"        readtex1 = textureLod(uTex1, vTexCoord1, 1.0);\n"
"      } else {											\n"
"        readtex0 = texture(uTex0, vTexCoord0);		\n"
"        readtex1 = texture(uTex1, vTexCoord1);		\n"
"      }												\n"
"    }													\n"
"  } else {												\n"
"    if (uTextureDetail == 2) {							\n"
"      readtex0 = textureLod(uTex1, vTexCoord1, lod_tile);		\n"
"      readtex1 = textureLod(uTex1, vTexCoord1, lod_tile + 1.0);	\n"
"    } else {														\n"
"      readtex0 = textureLod(uTex1, vTexCoord1, lod_tile - 1.0);	\n"
"      readtex1 = textureLod(uTex1, vTexCoord1, lod_tile);		\n"
"    }																\n"
"  }																\n"
"  return lod_frac;													\n"
"}																	\n"
#else
"in vec2 vTexCoord0;		\n"
"in vec2 vTexCoord1;		\n"
"in vec2 vLodTexCoord;		\n"
"uniform sampler2D uTex0;		\n"
"uniform sampler2D uTex1;		\n"
"uniform float uPrimLod;		\n"
"uniform int uEnableLod;		\n"
"uniform float uLodXScale;		\n"
"uniform float uLodYScale;		\n"
"uniform float uMinLod;			\n"
"uniform int uMaxTile;			\n"
"uniform int uTextureDetail;	\n"
"														\n"
"float mipmap(out vec4 readtex0, out vec4 readtex1) {	\n"
"  if (uEnableLod == 0) {								\n"
"    readtex0 = texture(uTex0, vTexCoord0);			\n"
"    readtex1 = texture(uTex1, vTexCoord1);			\n"
"    return uPrimLod;									\n"
"  }													\n"
"  vec2 dx = dFdx(vLodTexCoord);						\n"
"  dx.x *= uLodXScale;									\n"
"  dx.y *= uLodYScale;									\n"
"  vec2 dy = dFdy(vLodTexCoord);						\n"
"  dy.x *= uLodXScale;									\n"
"  dy.y *= uLodYScale;									\n"
"  float lod = max(length(dx), length(dy));				\n"
//" float lod = max(length(dx), length(dy)) * max(uLodXScale, uLodYScale);\n"
"  float lod_tile, lod_frac;							\n"
"  bool magnifying;										\n"
"  if (lod < 1.0) {										\n"
"    magnifying = true;									\n"
"    lod_tile = 0.0;									\n"
"    lod_frac = lod;									\n"
"    if (uTextureDetail != 0)							\n"
"      lod_frac = max(lod, uMinLod);					\n"
"    if (uTextureDetail == 1)							\n"
"      lod_frac = 1.0 - lod_frac;						\n"
"  } else {												\n"
"    magnifying = false;								\n"
"    lod_tile = min(float(uMaxTile), floor(log2(floor(lod)))); \n"
"    lod_frac = fract(lod/pow(2.0, lod_tile));			\n"
"  }													\n"
"  if (lod_tile < 1.0) {								\n"
"    if (magnifying) {									\n"
"      readtex0 = texture(uTex0, vTexCoord0);			\n"
//     !sharpen && !detail
"      if (uTextureDetail == 0) readtex1 = readtex0;	\n"
"      else readtex1 = texture(uTex1, vTexCoord1);	\n"
"    } else {											\n"
//     detail
"      if (uTextureDetail == 2) {						\n"
"        readtex0 = textureLod(uTex1, vTexCoord1, 0.0);\n"
"        readtex1 = textureLod(uTex1, vTexCoord1, 1.0);\n"
"      } else {											\n"
"        readtex0 = texture(uTex0, vTexCoord0);		\n"
"        readtex1 = texture(uTex1, vTexCoord1);		\n"
"      }												\n"
"    }													\n"
"  } else {												\n"
"    if (uTextureDetail == 2) {							\n"
"      readtex0 = textureLod(uTex1, vTexCoord1, lod_tile);		\n"
"      readtex1 = textureLod(uTex1, vTexCoord1, lod_tile + 1.0);	\n"
"    } else {														\n"
"      readtex0 = textureLod(uTex1, vTexCoord1, lod_tile - 1.0);	\n"
"      readtex1 = textureLod(uTex1, vTexCoord1, lod_tile);		\n"
"    }																\n"
"  }																\n"
"  return lod_frac;													\n"
"}																	\n"
#endif
;

#ifdef GL_IMAGE_TEXTURES_SUPPORT
static const char* depth_compare_shader_float =
"#version 420 core			\n"
"uniform int uEnableDepth;	\n"
"uniform int uDepthMode;		\n"
"uniform int uEnableDepthCompare;	\n"
"uniform int uEnableDepthUpdate;	\n"
"uniform mediump float uDepthTrans;			\n"
"uniform mediump float uDepthScale;			\n"
"layout(binding = 0, r16ui) uniform readonly uimage2D uZlutImage;\n"
"layout(binding = 2, rgba32f) uniform restrict image2D uDepthImage;\n"
"void write_depth(in highp float dz, in ivec2 coord)		\n"
"{															\n"
"  highp float fZ = 2.0*gl_FragCoord.z - 1.0;				\n"
"  fZ = (uDepthScale*fZ + uDepthTrans)*8.0;					\n"
"  const highp int iZ = int(floor(fZ + 0.5));				\n"
"  int y0 = clamp(iZ/512, 0, 511);							\n"
"  int x0 = iZ - 512*y0;									\n"
"  unsigned int iN64z = imageLoad(uZlutImage,ivec2(x0,y0)).r;\n"
"  highp float n64z = clamp(float(iN64z)/65532.0, 0.0, 1.0);\n"
"  highp vec4 depth = vec4(n64z, gl_FragCoord.z, dz, 1.0); \n"
"  memoryBarrier();											\n"
"  imageStore(uDepthImage,coord,depth);						\n"
"}															\n"
"lowp bool depth_compare()										\n"
"{															\n"
//"  if (uEnableDepth == 0) return true;						\n"
"  ivec2 coord = ivec2(gl_FragCoord.xy);					\n"
"  memoryBarrier();											\n"
"  highp vec4 depth = imageLoad(uDepthImage,coord);			\n"
"  highp float bufZ = depth.g;							\n"
"  highp float curZ = gl_FragCoord.z;					\n"
"  highp float dz = fwidth(gl_FragCoord.z);				\n"
"  highp float dzMax = max(dz, depth.b);			\n"
"  const bool bInfront = curZ < bufZ;					\n"
"  const bool bFarther = (curZ + dzMax) >= bufZ;		\n"
"  const bool bNearer = (curZ - dzMax) <= bufZ;			\n"
"  const bool bMax = bufZ == 1.0;						\n"
"  bool bRes;											\n"
"  switch(uDepthMode) {									\n"
"     case 0:											\n"
"     case 1:											\n"
"       bRes = bMax || bNearer;							\n"
"       break;											\n"
"     case 2:											\n"
"       bRes = bMax || bInfront;						\n"
"       break;											\n"
"     case 3:											\n"
"       bRes = bFarther && bNearer && !bMax;			\n"
"       break;											\n"
"     default:											\n"
"       bRes = bInfront;								\n"
"       break;											\n"
"  }													\n"
"  if (uEnableDepthUpdate != 0  && bRes) {				\n"
"	 write_depth(dz, coord);							\n"
"  }													\n"
"  if (uEnableDepthCompare != 0)						\n"
"    return bRes;										\n"
"  return true;											\n"
"}														\n"
;

static const char* shadow_map_vertex_shader =
"#version 420 core												\n"
"in highp vec4 	aPosition;								\n"
"void main()                                                    \n"
"{                                                              \n"
"  gl_Position = aPosition;										\n"
"}                                                              \n"
;

static const char* shadow_map_fragment_shader_float =
"#version 420 core											\n"
"layout(binding = 1, r16ui) uniform readonly uimage1D uTlutImage;\n"
"layout(binding = 2, rgba32f) uniform readonly image2D uDepthImage;\n"
"uniform lowp vec4 uFogColor;								\n"
"out lowp vec4 fragColor;									\n"
"lowp float get_alpha()										\n"
"{															\n"
"  ivec2 coord = ivec2(gl_FragCoord.xy);					\n"
"  mediump float bufZ = imageLoad(uDepthImage,coord).r;		\n"
"  int index = min(255, int(bufZ*255.0));					\n"
"  unsigned int iAlpha = imageLoad(uTlutImage,index).r; \n"
"  memoryBarrier();										\n"
"  return float(iAlpha/256)/255.0;						\n"
"}														\n"
"void main()											\n"
"{														\n"
"  fragColor = vec4(uFogColor.rgb, get_alpha());		\n"
"}														\n"
;
#endif // GL_IMAGE_TEXTURES_SUPPORT
