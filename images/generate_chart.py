import math

# Data
rssi = [-48, -53, -60, -71, -82]
speed = [6023.82, 5688.89, 4876.19, 3276.80, 1170.29]

width = 800
height = 500
pad_l = 90
pad_r = 50
pad_t = 60
pad_b = 70

plot_w = width - pad_l - pad_r
plot_h = height - pad_t - pad_b

# X range: -90 to -40
x_min, x_max = -90, -40
# Y range: 0 to 7000
y_min, y_max = 0, 7000

def to_svg_x(x):
    return pad_l + (x - x_min) / (x_max - x_min) * plot_w

def to_svg_y(y):
    return pad_t + (y_max - y) / (y_max - y_min) * plot_h

svg = []
svg.append(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" width="100%" height="100%" style="background:#ffffff; font-family: Segoe UI, Arial, sans-serif;">')

# Title
svg.append(f'<text x="{width/2}" y="36" text-anchor="middle" font-size="20" font-weight="bold" fill="#1e293b">ESP32 RSSI vs Throughput Profiling (Lab 6.2)</text>')

# Gridlines & Y-axis labels
for y_val in range(0, 7001, 1000):
    sy = to_svg_y(y_val)
    svg.append(f'<line x1="{pad_l}" y1="{sy}" x2="{width - pad_r}" y2="{sy}" stroke="#e2e8f0" stroke-width="1" stroke-dasharray="4,4"/>')
    svg.append(f'<text x="{pad_l - 12}" y="{sy + 4}" text-anchor="end" font-size="12" fill="#64748b">{y_val:,}</text>')

# Gridlines & X-axis labels
for x_val in range(-90, -39, 10):
    sx = to_svg_x(x_val)
    svg.append(f'<line x1="{sx}" y1="{pad_t}" x2="{sx}" y2="{height - pad_b}" stroke="#e2e8f0" stroke-width="1" stroke-dasharray="4,4"/>')
    svg.append(f'<text x="{sx}" y="{height - pad_b + 22}" text-anchor="middle" font-size="12" fill="#64748b">{x_val} dBm</text>')

# Axes
svg.append(f'<line x1="{pad_l}" y1="{height - pad_b}" x2="{width - pad_r}" y2="{height - pad_b}" stroke="#475569" stroke-width="2"/>')
svg.append(f'<line x1="{pad_l}" y1="{pad_t}" x2="{pad_l}" y2="{height - pad_b}" stroke="#475569" stroke-width="2"/>')

# Axis Titles
svg.append(f'<text x="{width/2}" y="{height - 18}" text-anchor="middle" font-size="14" font-weight="600" fill="#334155">RSSI Signal Strength (dBm)</text>')
svg.append(f'<text transform="rotate(-90)" x="-{height/2}" y="28" text-anchor="middle" font-size="14" font-weight="600" fill="#334155">Throughput Speed (Kbps)</text>')

# 50% Threshold line at y = 3000
thresh_y = to_svg_y(3000)
svg.append(f'<line x1="{pad_l}" y1="{thresh_y}" x2="{width - pad_r}" y2="{thresh_y}" stroke="#ef4444" stroke-width="2" stroke-dasharray="6,4"/>')
svg.append(f'<rect x="{width - pad_r - 215}" y="{thresh_y - 24}" width="210" height="20" rx="4" fill="#fee2e2"/>')
svg.append(f'<text x="{width - pad_r - 10}" y="{thresh_y - 10}" text-anchor="end" font-size="11" font-weight="bold" fill="#b91c1c">50% Threshold (3,000 Kbps at ~ -73 dBm)</text>')

# Trendline (Linear: y = 143.83x + 13120.3)
x1_fit, x2_fit = -85, -45
y1_fit = 143.83 * x1_fit + 13120.3
y2_fit = 143.83 * x2_fit + 13120.3
svg.append(f'<line x1="{to_svg_x(x1_fit)}" y1="{to_svg_y(y1_fit)}" x2="{to_svg_x(x2_fit)}" y2="{to_svg_y(y2_fit)}" stroke="#2563eb" stroke-width="2.5" stroke-dasharray="5,5"/>')

# Data points & Labels
for i in range(len(rssi)):
    cx = to_svg_x(rssi[i])
    cy = to_svg_y(speed[i])
    svg.append(f'<circle cx="{cx}" cy="{cy}" r="7" fill="#0284c7" stroke="#ffffff" stroke-width="2.5" />')
    # Point labels
    label = f"{speed[i]:,.0f} Kbps"
    label_y = cy - 14 if i != 4 else cy - 14
    svg.append(f'<text x="{cx}" y="{label_y}" text-anchor="middle" font-size="11" font-weight="bold" fill="#0f172a">{label}</text>')
    svg.append(f'<text x="{cx}" y="{label_y + 11}" text-anchor="middle" font-size="10" fill="#64748b">({rssi[i]} dBm)</text>')

# Legend / Equation Box
box_x = pad_l + 20
box_y = pad_t + 15
svg.append(f'<rect x="{box_x}" y="{box_y}" width="250" height="75" rx="6" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1.5"/>')
svg.append(f'<circle cx="{box_x + 18}" cy="{box_y + 20}" r="5" fill="#0284c7"/>')
svg.append(f'<text x="{box_x + 32}" y="{box_y + 24}" font-size="12" fill="#1e293b" font-weight="600">Measured Data Points</text>')
svg.append(f'<line x1="{box_x + 10}" y1="{box_y + 42}" x2="{box_x + 26}" y2="{box_y + 42}" stroke="#2563eb" stroke-width="2.5" stroke-dasharray="4,3"/>')
svg.append(f'<text x="{box_x + 32}" y="{box_y + 46}" font-size="12" fill="#2563eb" font-weight="600">y = 143.8x + 13,120 (R² = 0.964)</text>')
svg.append(f'<line x1="{box_x + 10}" y1="{box_y + 62}" x2="{box_x + 26}" y2="{box_y + 62}" stroke="#ef4444" stroke-width="2" stroke-dasharray="4,2"/>')
svg.append(f'<text x="{box_x + 32}" y="{box_y + 66}" font-size="11" fill="#b91c1c" font-weight="bold">Threshold &gt; 50% Drop</text>')

svg.append('</svg>')

output_path = r"c:\ioT-Tue\Week-06-Wi-Fi-AP-Throughput-FreeRTOS\images\rssi_throughput_plot.svg"
with open(output_path, "w", encoding="utf-8") as f:
    f.write("\n".join(svg))
print("Chart generated successfully at:", output_path)
