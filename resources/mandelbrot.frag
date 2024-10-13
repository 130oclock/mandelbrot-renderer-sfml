#define samples 4
#define log2 0.69314718055994528622676398299518041312694549560546875
#define ilog2 1.442695040888963387004650940070860087871551513671875

uniform vec2 u_resolution;
uniform int u_maxIterations;
uniform vec2 u_center;
uniform float u_zoom;

// Utility functions
float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float rseed = 0.0;
vec2 rand2() {
    vec2 seed = vec2(rseed++, rseed++);
    return vec2(rand(seed + 0.342), rand(seed + 0.756));
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d ) {
    return a + b*cos(6.28318*(c*t+d));
}

// Mandelbrot implementation
vec3 getColor(float i) {
    vec3 color;

    float f = i / float(u_maxIterations);

    //color = hsv2rgb(vec3(mod(pow(f * 360.0, 1.5), 360.0) / 360.0, 1.0, f));
    color = palette(cos(31.41592 * f) + 0.5, vec3(0.5), vec3(0.5), vec3(1.0), vec3(0.0, 0.1, 0.2));

    return color;
}

float iterate(vec2 c) {
    int i;
    float x = 0.0, y = 0.0, x2 = 0.0, y2 = 0.0;

    for (i = 0; (x2 + y2 <= 4.0) && i < u_maxIterations; ++i) {
        y = c.y + (x + x) * y;
        x = c.x + x2 - y2;
        x2 = x * x;
        y2 = y * y;
    }

    if (i < u_maxIterations) {
        float log_zn = log(x2 + y2) * 0.5;
        float nu = log(log_zn * ilog2) * ilog2;

        return float(i) + 1.0 - nu;
    }

    return float(i);
}

void main() {
    vec3 color = vec3(0.0);

    for (int sample = 0; sample < samples; ++sample) {
        vec2 uv = u_zoom * (2.0 * gl_FragCoord.xy + rand2() - u_resolution) / u_resolution.x + u_center;

        uv = vec2(uv.x, -uv.y);

        float i = iterate(uv);

        if (int(i) < u_maxIterations)
            color += getColor(i);
    }

    gl_FragColor = vec4(color.xyz / float(samples), 1.0);
}