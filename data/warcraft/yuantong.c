// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小虎[2;37;0m[2;37;0m", ({"tong"}));        
        set("gender", "男性");                
        set("long", "阿达发生地方公司分管[2;37;0m
它是慧通的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yuantong");
        set("owner_name", "慧通");
        set_temp("owner", "yuantong");
        set_temp("owner_name", "慧通");
        ::setup();
}
