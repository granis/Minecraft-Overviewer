====================================
Minecraft Overviewer - fork
====================================
By Andrew Brown and contributors (see CONTRIBUTORS.rst).

Fork in use at https://www.xtralarge.se

Features:

* **Grass** on sides: https://maps.xtralarge.se/#/-10583/64/10301/-2/Terranova/terranova_day

* **Snow** instead of dirt on sides: https://maps.xtralarge.se/#/-6458/64/11369/-2/Terranova/terranova_day

* **Extra virtual zoom** in Leaflet for that pixel perfect-inspection

* **Biomes** updated to 1.18/1.19, including **coloring on water/foliage**. Example: https://maps.xtralarge.se/#/1326/64/17296/-4/Terranova/terranova_day

* **Diskcache** for textures, meaning **1sec** boot instead of generating for minutes every launch.

* Extra LRU-cache for get_chunk since its called so frequently, resulting in **faster rendering**.
