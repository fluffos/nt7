// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m纯阳无极兽[2;37;0m[2;37;0m", ({"gzyds"}));        
        set("gender", "男性");                
        set("long", "一只刚猛绝伦的麒麟，乃天生地化，日月之精华所成[2;37;0m
它是顾正阳的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gzy");
        set("owner_name", "顾正阳");
        set_temp("owner", "gzy");
        set_temp("owner_name", "顾正阳");
        ::setup();
}
