// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白骆驼[2;37;0m[2;37;0m[2;37;0m", ({"baituoer"}));        
        set("gender", "女性");                
        set("long", "厉害的骆驼[2;37;0m
它是拜托的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "baituo");
        set("owner_name", "拜托");
        set_temp("owner", "baituo");
        set_temp("owner_name", "拜托");
        ::setup();
}
