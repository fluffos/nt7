// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("佛祖[2;37;0m[2;37;0m", ({"kkkke"}));        
        set("gender", "男性");                
        set("long", "工作吧[2;37;0m
它是无无人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wcawan");
        set("owner_name", "无无人");
        set_temp("owner", "wcawan");
        set_temp("owner_name", "无无人");
        ::setup();
}
