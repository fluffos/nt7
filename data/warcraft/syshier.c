// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("疯狂狮子[2;37;0m[2;37;0m", ({"mushiz"}));        
        set("gender", "女性");                
        set("long", "疯狂狮子—做爱疯狂无止境[2;37;0m
它是霸剑盟的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "syshier");
        set("owner_name", "霸剑盟");
        set_temp("owner", "syshier");
        set_temp("owner_name", "霸剑盟");
        ::setup();
}
