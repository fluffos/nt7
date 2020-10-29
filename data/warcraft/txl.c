// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大鸟[2;37;0m[2;37;0m", ({"quer"}));        
        set("gender", "女性");                
        set("long", "大[2;37;0m
它是泰旋的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txl");
        set("owner_name", "泰旋");
        set_temp("owner", "txl");
        set_temp("owner_name", "泰旋");
        ::setup();
}
