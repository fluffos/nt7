// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火炉[2;37;0m[2;37;0m", ({"huohu"}));        
        set("gender", "女性");                
        set("long", "烈火熊熊[2;37;0m
它是烤肉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "linlinlin");
        set("owner_name", "烤肉");
        set_temp("owner", "linlinlin");
        set_temp("owner_name", "烤肉");
        ::setup();
}
