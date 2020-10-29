// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m飞鸟一现[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "飞呀飞呀[2;37;0m
它是胡一飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mavis");
        set("owner_name", "胡一飞");
        set_temp("owner", "mavis");
        set_temp("owner_name", "胡一飞");
        ::setup();
}
