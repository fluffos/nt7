// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m梅花鹿[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "$HIY$梅花鹿[2;37;0m
它是孙思邈的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miao");
        set("owner_name", "孙思邈");
        set_temp("owner", "miao");
        set_temp("owner_name", "孙思邈");
        ::setup();
}
