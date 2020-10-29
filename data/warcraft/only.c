// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m玲珑[2;37;0m[2;37;0m", ({"firebird"}));        
        set("gender", "女性");                
        set("long", "一只红色的大鸟，很大，很红！[2;37;0m
它是慕容无双的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "only");
        set("owner_name", "慕容无双");
        set_temp("owner", "only");
        set_temp("owner_name", "慕容无双");
        ::setup();
}
