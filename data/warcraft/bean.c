// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武灵兽[2;37;0m[2;37;0m", ({"beansxuanwu"}));        
        set("gender", "男性");                
        set("long", "玄武灵兽[2;37;0m
它是张豆子的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "bean");
        set("owner_name", "张豆子");
        set_temp("owner", "bean");
        set_temp("owner_name", "张豆子");
        ::setup();
}
