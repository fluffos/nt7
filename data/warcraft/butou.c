// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m爪电[1;33m飞黄[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这西域神驹浑身黄金缎子似的，只有四蹄黑色，绝影追光。[2;37;0m
它是邢捕头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "butou");
        set("owner_name", "邢捕头");
        set_temp("owner", "butou");
        set_temp("owner_name", "邢捕头");
        ::setup();
}
