// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m路虎[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "$HIB$路虎[2;37;0m
它是凯旋王的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wang");
        set("owner_name", "凯旋王");
        set_temp("owner", "wang");
        set_temp("owner_name", "凯旋王");
        ::setup();
}
