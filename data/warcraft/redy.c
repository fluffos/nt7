// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m红莲妹纸[2;37;0m[2;37;0m", ({"gold"}));        
        set("gender", "男性");                
        set("long", "红莲老祖的化身[2;37;0m
它是红花老妖的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "redy");
        set("owner_name", "红花老妖");
        set_temp("owner", "redy");
        set_temp("owner_name", "红花老妖");
        ::setup();
}
