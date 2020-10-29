// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎虎虎[2;37;0m[2;37;0m", ({"xiaobaihu"}));        
        set("gender", "男性");                
        set("long", "虎虎虎[2;37;0m
它是日落的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "shsjg");
        set("owner_name", "日落");
        set_temp("owner", "shsjg");
        set_temp("owner_name", "日落");
        ::setup();
}
