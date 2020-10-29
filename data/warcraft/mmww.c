// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m真[1;31m武[2;37;0m[2;37;0m", ({"zhenwu"}));        
        set("gender", "男性");                
        set("long", "大帝[2;37;0m
它是北漠的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mmww");
        set("owner_name", "北漠");
        set_temp("owner", "mmww");
        set_temp("owner_name", "北漠");
        ::setup();
}
