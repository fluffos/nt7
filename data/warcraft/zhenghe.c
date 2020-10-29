// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m心坚[2;37;0m[2;37;0m", ({"xinjian"}));        
        set("gender", "男性");                
        set("long", "一只天赋异禀却有残疾的乌龟[2;37;0m
它是郑和的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zhenghe");
        set("owner_name", "郑和");
        set_temp("owner", "zhenghe");
        set_temp("owner_name", "郑和");
        ::setup();
}
