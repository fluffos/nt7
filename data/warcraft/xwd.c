// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m白[1;37m[33m虎[2;37;0m[2;37;0m", ({"xwdh"}));        
        set("gender", "男性");                
        set("long", "白小虎[2;37;0m
它是谢文东的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xwd");
        set("owner_name", "谢文东");
        set_temp("owner", "xwd");
        set_temp("owner_name", "谢文东");
        ::setup();
}
