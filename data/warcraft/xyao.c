// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;37m神器[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "shit[2;37;0m
它是小遥的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyao");
        set("owner_name", "小遥");
        set_temp("owner", "xyao");
        set_temp("owner_name", "小遥");
        ::setup();
}
