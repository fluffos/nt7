// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("果园[2;37;0m[2;37;0m", ({"guoyuan"}));        
        set("gender", "女性");                
        set("long", "绿草清清[2;37;0m
它是橘子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "juzi");
        set("owner_name", "橘子");
        set_temp("owner", "juzi");
        set_temp("owner_name", "橘子");
        ::setup();
}
