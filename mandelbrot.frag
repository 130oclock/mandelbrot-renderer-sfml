uniform vec2 u_resolution;
uniform int u_maxIterations;

uniform vec2 u_center;
uniform float u_zoom;

float log_2 = 0.30102999566;

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 getColor(float i) {
    float f = float(i) / float(u_maxIterations);

    float h = mod(pow(f * 360.0, 1.5), 360.0) / 360.0;
    float s = 1.0;
    float v = f;

    return hsv2rgb(vec3(h, s, v));
}

float getMandelbrot(vec2 c) {
    int i;
    float x = 0.0, y = 0.0, x2 = 0.0, y2 = 0.0;

    for (i = 0; x2 + y2 <= 4.0 && i < u_maxIterations; ++i) {
        y = (x + x) * y + c.y;
        x = x2 - y2 + c.x;
        x2 = x * x;
        y2 = y * y;
    }

    if (i < u_maxIterations) {
        float log_zn = log(x2 + y2) * 0.5;
        float nu = log(log_zn / log_2) / log_2;

        return 1.0 + float(i) - nu;
    }

    return float(i);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;

    // Move (0, 0) to center of window
    uv -= 0.5;

    // Adjust for aspect ratio
    uv.y = uv.y * (u_resolution.y / u_resolution.x);
    // Scale to fit the screen
    uv = uv * 4.0 * u_zoom;
    uv += u_center;

    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

    float i = getMandelbrot(uv);

    if (int(i) < u_maxIterations)
        gl_FragColor = vec4(getColor(i).xyz, 1.0);
}