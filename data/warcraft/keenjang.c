// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m移动睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "只要躺在它背上就可以美美的睡上一觉。[2;37;0m
它是风清扬的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "keenjang");
        set("owner_name", "风清扬");
        set_temp("owner", "keenjang");
        set_temp("owner_name", "风清扬");
        ::setup();
}
