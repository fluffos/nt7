// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m史[1;35m塔[1;32m克[2;37;0m[2;37;0m", ({"stk"}));        
        set("gender", "女性");                
        set("long", "哈哈哈[2;37;0m
它是珊莎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sansa");
        set("owner_name", "珊莎");
        set_temp("owner", "sansa");
        set_temp("owner_name", "珊莎");
        ::setup();
}
