// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青儿[2;37;0m[2;37;0m", ({"qinger"}));        
        set("gender", "女性");                
        set("long", "一条碧绿青蛇[2;37;0m
它是千夜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yangjip");
        set("owner_name", "千夜");
        set_temp("owner", "yangjip");
        set_temp("owner_name", "千夜");
        ::setup();
}
