// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m墨玉麒麟[2;37;0m[2;37;0m", ({"qi_lin"}));        
        set("gender", "男性");                
        set("long", "墨玉麒麟[2;37;0m
它是星宿老妖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "smja");
        set("owner_name", "星宿老妖");
        set_temp("owner", "smja");
        set_temp("owner_name", "星宿老妖");
        ::setup();
}
