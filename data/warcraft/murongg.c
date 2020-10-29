// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m红粉佳人[2;37;0m[2;37;0m", ({"hongjia"}));        
        set("gender", "女性");                
        set("long", "窈窕美女，君子好求。[2;37;0m
它是慕容城的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "murongg");
        set("owner_name", "慕容城");
        set_temp("owner", "murongg");
        set_temp("owner_name", "慕容城");
        ::setup();
}
