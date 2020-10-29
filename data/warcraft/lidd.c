// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小卓起[2;37;0m[2;37;0m", ({"zhuoqi"}));        
        set("gender", "女性");                
        set("long", "小卓起[2;37;0m
它是炼风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidd");
        set("owner_name", "炼风");
        set_temp("owner", "lidd");
        set_temp("owner_name", "炼风");
        ::setup();
}
