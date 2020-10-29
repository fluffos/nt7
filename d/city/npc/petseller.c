#include <ansi.h>
inherit NPC;

int check_legal_name(string arg);
int check_legal_id(string arg);

void create()
{
        set_name("翩翩", ({ "pian pian" }) );
        set("gender", "女性" );
        set("age", 22);
        set("long",@LONG
翩翩姓张，后嫁给一小土财主，财主过世后就开使每天背一个小筐卖宠物。你要
喜欢宠物的话，不妨也养(yang)一只玩玩。
LONG );
        set("title",HIW"宠物小贩"NOR);
        set("combat_exp", 5);
        set("chat_chance", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{       
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_yang", "yang");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "翩翩说道：这位" + RANK_D->query_respect(ob)
                                + "，要买小猫小狗么？\n");
                        break;
                case 1:
                        say( "翩翩说道：这位" + RANK_D->query_respect(ob)
                                + "，你太穷酸了，我不卖给你。\n");
                        break;
        }
}

int do_yang(string arg)
{
        string ctype, cname, ccolor, cid, ownername, result;
        object ob, me, gold;
        string id,filename;
        object newpet;

        me = this_player();
        id=query("id", me);
        ownername = me->name(1);
        
        if(!arg || sscanf(arg,"%s %s %s %s",ctype,ccolor,cname,cid ) != 4)
        {
                write(@LONG
指令格式：yang <type> <color> <name> <english name>
可以养的宠物种类有：
        小狗：dog       小猫：cat       小猪：pig       小鹰：hawk
        小猴：monkey    小鸭：duck      小鸡：hen
宠物可选的颜色有：
        $RED$ - 红色    $HIR$ - 亮红色  $YEL$ - 土黄色
        $GRN$ - 绿色    $HIG$ - 亮绿色  $BLU$ - 深蓝色
        $HIY$ - 黄色    $MAG$ - 浅紫色  $HIM$ - 粉红色
        $HIB$ - 蓝色    $HIC$ - 天青色  $CYN$ - 蓝绿色
        $HIW$ - 白色    $WHT$ - 浅灰色  $NOR$ - 正常颜色
其它与宠物有关的介绍请help pet参考相关的说明。
LONG );                
                return 1;
        }
        if(me->is_busy())
                return notify_fail("你上一个动作还没有完成。\n");
        if(file_size( me->query_save_file() + ".pet.o") > 0)
                return notify_fail("你已经拥有你心爱的宠物了。\n");
        gold = present("gold_money", this_player());
        if(!gold)
                return notify_fail("你身上没有金子。\n");
        if((int) gold->query_amount() < 100)
                return notify_fail("你身上没有那麽多金子。\n");
        if( query("score", me)<500 )
                return notify_fail("你的评价不够。\n");
                
        if( (ownername != cname) && (stringp(result = NAME_D->invalid_new_name(cname))) )
        {
                write("对不起，" + result);
                write(HIR"禁止使用与他人姓名相同或接近的宠物名。并因循RULES中对名字的相关规定。"NOR+"\n");
                return 1;
        }
            
        if( !check_legal_name(cname))
                return notify_fail("");
        if( !check_legal_id(cid))
                return notify_fail("");

        if( ccolor != "$NOR$" &&
            ccolor != "$RED$" &&
            ccolor != "$GRN$" &&
            ccolor != "$YEL$" &&
            ccolor != "$BLU$" &&
            ccolor != "$MAG$" &&
            ccolor != "$CYN$" &&
            ccolor != "$WHT$" &&
            ccolor != "$HIR$" &&
            ccolor != "$HIG$" &&
            ccolor != "$HIY$" &&
            ccolor != "$HIB$" &&
            ccolor != "$HIM$" &&
            ccolor != "$HIC$" &&
            ccolor != "$HIW$" 
        )
        return
                notify_fail("不知你要什么颜色．\n");
        cname = ccolor + cname;
        if(ccolor != "$NOR$")
        {
                cname = replace_string(cname, "$RED$", RED);
                cname = replace_string(cname, "$GRN$", GRN);
                cname = replace_string(cname, "$YEL$", YEL);
                cname = replace_string(cname, "$BLU$", BLU);
                cname = replace_string(cname, "$MAG$", MAG);
                cname = replace_string(cname, "$CYN$", CYN);
                cname = replace_string(cname, "$WHT$", WHT);
                cname = replace_string(cname, "$HIR$", HIR);
                cname = replace_string(cname, "$HIG$", HIG);
                cname = replace_string(cname, "$HIY$", HIY);
                cname = replace_string(cname, "$HIB$", HIB);
                cname = replace_string(cname, "$HIM$", HIM);
                cname = replace_string(cname, "$HIC$", HIC);
                cname = replace_string(cname, "$HIW$", HIW);
                cname += NOR;
        }
        seteuid(ROOT_UID);
        newpet = new("/clone/misc/pet");        
        switch( ctype ) {
                case "dog":
                        set("title", "小狗", newpet);
                        set("int", 5+random(10), newpet);
                        break;
                case "cat":
                        set("title", "小猫", newpet);
                        set("per", 5+random(10), newpet);
                        break;
                case "pig":
                        set("title", "小猪", newpet);
                        set("str", 5+random(10), newpet);
                        break;
                case "monkey":
                        set("title", "小猴", newpet);
                        set("dex", 5+random(10), newpet);
                        break;
                case "duck":
                        set("title", "小鸭", newpet);
                        set("con", 5+random(10), newpet);
                        break;
                case "hen":
                        set("title", "小鸡", newpet);
                        set("con", 5+random(10), newpet);
                        break;
                case "hawk":
                        set("title", "小鹰", newpet);
                        set("dex", 5+random(2), newpet);
                        break;
                default:
                        return notify_fail("这里没有你要的东西。\n");
        }
        set("owner",query("id",  me), newpet);
        set("possessed", me, newpet);
        set("name", cname, newpet);
        set("id", cid, newpet);
        set("long", "一只"+ownername+"养的"+query("title", newpet)+"。", newpet);
        newpet->save();
        destruct(newpet);
        gold->add_amount(-100);
        addn("score", -500, me);
        me->start_busy(1);
        command("say 你试着吹一声口哨(whistle)，你的小宝宝就会跑过来的！");
        seteuid(getuid());
        return 1;
}

int check_legal_name(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 10 ) ) {
                write("对不起，中文名字必须是一到五个中文字。\n");
                return 0;
        }
        while(i--) {
                if( name[i]<=' ' ) {
                        write("对不起，中文名字不能用控制字元。\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(name[i..<0]) ) {
                        write("对不起，名字必需是中文。\n");
                        return 0;
                }
        }
        return 1;
}

int check_legal_id(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 3) || (strlen(name) > 20 ) ) {
                write("对不起，英文名字必须是三到二十个字。\n");
                return 0;
        }

        return 1;
}
