// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "中国古代神话传说中的神兽，据说能活两千年。[2;37;0m
它是制药机的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "viagra");
        set("owner_name", "制药机");
        set_temp("owner", "viagra");
        set_temp("owner_name", "制药机");
        ::setup();
}
