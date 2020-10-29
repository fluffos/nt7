// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("妹子[2;37;0m[2;37;0m", ({"lsj"}));        
        set("gender", "女性");                
        set("long", "妹子[2;37;0m
它是随灵的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "clipzero");
        set("owner_name", "随灵");
        set_temp("owner", "clipzero");
        set_temp("owner_name", "随灵");
        ::setup();
}
