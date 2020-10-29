// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "$HIR$火麒麟[2;37;0m
它是吉祥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "baolna");
        set("owner_name", "吉祥");
        set_temp("owner", "baolna");
        set_temp("owner_name", "吉祥");
        ::setup();
}
