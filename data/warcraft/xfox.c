// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m大玄武[2;37;0m[2;37;0m", ({"daxuanwu"}));        
        set("gender", "女性");                
        set("long", "大[2;37;0m
它是妖狐千年的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xfox");
        set("owner_name", "妖狐千年");
        set_temp("owner", "xfox");
        set_temp("owner_name", "妖狐千年");
        ::setup();
}
