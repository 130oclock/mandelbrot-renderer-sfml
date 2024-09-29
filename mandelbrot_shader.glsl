uniform vec2 u_resolution;
uniform int u_maxIterations;

uniform vec2 u_center;
uniform float u_zoom;


void main() {
    vec2 c = gl_FragCoord.xy / u_resolution;

    // Move (0, 0) to center of window
    c = c - 0.5;
    // Adjust for aspect ratio
    c.y = c.y * u_resolution.y / u_resolution.x;
    // Scale to fit the screen
    c = c * 4.0 / u_zoom;

    c = c + u_center;

    int i = 0;
    float x = 0.0, y = 0.0, x2 = 0.0, y2 = 0.0;
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

    while (x2 + y2 <= 4.0 && i < u_maxIterations) {
        y = (x + x) * y + c.y;
        x = x2 - y2 + c.x;
        x2 = x * x;
        y2 = y * y;
        ++i;
    }

    if (i < u_maxIterations) {
        float s = float(i) / float(u_maxIterations);
        gl_FragColor = vec4(s, s, s, 1.0);
    }
}