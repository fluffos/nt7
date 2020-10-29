// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m金矿[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "money[2;37;0m
它是金五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cashe");
        set("owner_name", "金五");
        set_temp("owner", "cashe");
        set_temp("owner_name", "金五");
        ::setup();
}
