// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "大[2;37;0m
它是长神岛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "changansd");
        set("owner_name", "长神岛");
        set_temp("owner", "changansd");
        set_temp("owner_name", "长神岛");
        ::setup();
}
