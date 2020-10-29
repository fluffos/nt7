// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m烟花[2;37;0m[2;37;0m", ({"yhh"}));        
        set("gender", "女性");                
        set("long", "火红的烟花[2;37;0m
它是聂霜卿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nsq");
        set("owner_name", "聂霜卿");
        set_temp("owner", "nsq");
        set_temp("owner_name", "聂霜卿");
        ::setup();
}
