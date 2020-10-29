// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "女性");                
        set("long", "墨鱼噢[2;37;0m
它是熊大的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "uliand");
        set("owner_name", "熊大");
        set_temp("owner", "uliand");
        set_temp("owner_name", "熊大");
        ::setup();
}
