// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m烈焰红唇[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是梅艳芳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "meiyanfang");
        set("owner_name", "梅艳芳");
        set_temp("owner", "meiyanfang");
        set_temp("owner_name", "梅艳芳");
        ::setup();
}
