// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "女性");                
        set("long", "玄武[2;37;0m
它是文章辉的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "skpa");
        set("owner_name", "文章辉");
        set_temp("owner", "skpa");
        set_temp("owner_name", "文章辉");
        ::setup();
}
