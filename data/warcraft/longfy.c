// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m灵魂深处[2;37;0m[2;37;0m", ({"lhsc"}));        
        set("gender", "男性");                
        set("long", "灵魂深处[2;37;0m
它是龙飞云的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "longfy");
        set("owner_name", "龙飞云");
        set_temp("owner", "longfy");
        set_temp("owner_name", "龙飞云");
        ::setup();
}
