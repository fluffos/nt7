// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m葵花[2;37;0m[2;37;0m", ({"kis"}));        
        set("gender", "男性");                
        set("long", "$HIR$葵花[2;37;0m
它是修罗的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "keer");
        set("owner_name", "修罗");
        set_temp("owner", "keer");
        set_temp("owner_name", "修罗");
        ::setup();
}
