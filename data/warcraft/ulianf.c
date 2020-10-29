// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "女性");                
        set("long", "墨鱼噢[2;37;0m
它是冒牌黑手的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ulianf");
        set("owner_name", "冒牌黑手");
        set_temp("owner", "ulianf");
        set_temp("owner_name", "冒牌黑手");
        ::setup();
}
