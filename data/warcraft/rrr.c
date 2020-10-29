// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "女性");                
        set("long", "玄武[2;37;0m
它是火星异种的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "rrr");
        set("owner_name", "火星异种");
        set_temp("owner", "rrr");
        set_temp("owner_name", "火星异种");
        ::setup();
}
