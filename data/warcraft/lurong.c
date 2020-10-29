// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红莲道人[2;37;0m[2;37;0m", ({"rod"}));        
        set("gender", "男性");                
        set("long", "$HIR$红莲道人[2;37;0m
它是鹿茸的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lurong");
        set("owner_name", "鹿茸");
        set_temp("owner", "lurong");
        set_temp("owner_name", "鹿茸");
        ::setup();
}
