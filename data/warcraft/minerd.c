// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老黄牛[2;37;0m[2;37;0m", ({"minerride"}));        
        set("gender", "男性");                
        set("long", "长得有点猥琐[2;37;0m
它是牛四的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "minerd");
        set("owner_name", "牛四");
        set_temp("owner", "minerd");
        set_temp("owner_name", "牛四");
        ::setup();
}
