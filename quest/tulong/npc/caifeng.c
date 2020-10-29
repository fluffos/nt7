// waiter.c
inherit NPC;
int check_legal_name(string arg);
int check_legal_id(string arg);

void create()
{
        set_name("老裁缝", ({ "waiter" }) );
        set("gender", "男性" );
        set("age", 52);
        set("long",
                "这位老裁缝正笑咪咪地忙著，还不时的擦一擦自己的老花眼。\n");
        set("combat_exp", 5);
        set("attitude", "friendly");
        setup();

}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_ding", "ding");

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "老裁缝笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，进来订身衣服吧。\n");
                        break;
                case 1:
                        say( "老裁缝愁眉苦脸说道：这位" + RANK_D->query_respect(ob)
                                + "，你又胖又矮，这帮不了你。\n");
                        break;
        }
}

int do_ding(string arg)
{
        string ctype, cname, ccolor, cid, material;
        object ob, me, gold, ob2;
        string id,newfile,filename,timestamp;
        me = this_player();
        id=query("id", me);
        if(!arg || sscanf(arg,"%s %s %s %s %s",ctype,ccolor,cname,cid,material ) != 5)
        return notify_fail("指令格式：ding <type> <color> <name> <English name> <material>\n");
        if(me->is_busy())
        return notify_fail("你上一个动作还没有完成。\n");
        if( query("created_item", me) >= query("age", me)/11 )
        return notify_fail("你现在只能拥有"+chinese_number(query("age", me)/11)+
"件自造物品。\n");
        if( query("created_item", me) >= 3 )
        return notify_fail("你已经拥有太多自造物品了。\n");
        gold = present("gold_money", this_player());
        if(!gold) return notify_fail("你身上没有金子。\n");
        if((int) gold->query_amount() < 1)
        return notify_fail("你身上没有那麽多金子。\n");
        if(!objectp(ob2=present(material,me)))
        return notify_fail("你身上并没有"+material+"。\n");
        if( !query("for_create_cloth", ob2) )
        return notify_fail(ob2->name()+"并不可以用来做衣饰。\n");
        if( !check_legal_name(cname))
        return notify_fail("");
        if( !check_legal_id(cid))
        return notify_fail("");

        if( ccolor != "$BLK$" && 
            ccolor != "$NOR$" &&
            ccolor != "$RED$" &&
            ccolor != "$GRN$" &&
            ccolor != "$YEL$" &&
            ccolor != "$BLU$" &&
            ccolor != "$MAG$" &&
            ccolor != "$CYN$" &&
            ccolor != "$WHT$" &&
            ccolor != "$NOR$" &&
            ccolor != "$HIR$" &&
            ccolor != "$HIG$" &&
            ccolor != "$HIY$" &&
            ccolor != "$HIB$" &&
            ccolor != "$HIM$" &&
            ccolor != "$HIC$" &&
            ccolor != "$HIW$" 
        )
        return notify_fail("不知你要什么颜色．\n");
        ccolor = replace_string(ccolor, "$BLK$", "BLK");
        ccolor = replace_string(ccolor, "$RED$", "RED");
        ccolor = replace_string(ccolor, "$GRN$", "GRN");
        ccolor = replace_string(ccolor, "$YEL$", "YEL");
        ccolor = replace_string(ccolor, "$BLU$", "BLU");
        ccolor = replace_string(ccolor, "$MAG$", "MAG");
        ccolor = replace_string(ccolor, "$CYN$", "CYN");
        ccolor = replace_string(ccolor, "$WHT$", "WHT");
        ccolor = replace_string(ccolor, "$HIR$", "HIR");
        ccolor = replace_string(ccolor, "$HIG$", "HIG");
        ccolor = replace_string(ccolor, "$HIY$", "HIY");
        ccolor = replace_string(ccolor, "$HIB$", "HIB");
        ccolor = replace_string(ccolor, "$HIM$", "HIM");
        ccolor = replace_string(ccolor, "$HIC$", "HIC");
        ccolor = replace_string(ccolor, "$HIW$", "HIW");
        ccolor = replace_string(ccolor, "$NOR$", "NOR");
        seteuid(ROOT_UID);
        switch( ctype ) {
                case "hat":
                        newfile = read_file("/obj/clothes/hat.o");
                        break;
                case "belt":
                        newfile = read_file("/obj/clothes/belt.o");
                        break;
                case "shoes":
                        newfile = read_file("/obj/clothes/shoes.o");
                        break;
                case "suit":
                        newfile = read_file("/obj/clothes/suit.o");
                        break;
                case "scarf":
                        newfile = read_file("/obj/clothes/scarf.o");
                        break;
                default:
                        return notify_fail("这里不会做你要的东西．\n");
        }
        timestamp = sprintf("%c%c%c%c%c%c%c",'a'+random(20),'a'+random(20),'a'+random(20),
        'a'+random(20),'a'+random(20),'a'+random(20),'a'+random(20));
        newfile = replace_string( newfile, "订作的", cname);
        newfile = replace_string( newfile, "order", cid);
        newfile = replace_string( newfile, "fengyun", id);
        newfile = replace_string( newfile, "COR", ccolor);
        newfile = replace_string( newfile, "STAMP", timestamp);
        filename = DATA_DIR+"login/" + id[0..0] + "/" + id + "/" + id +timestamp + ".c";
        if( !write_file(filename, newfile,1))
                return 0;
        ob = new(filename);
        if( query("equipped", ob2)){ob2->unequip();me->reset_action();}
        ob2->move(environment(me));
        set("weight", ob2->query_weight(), ob);
        set("armor_prop/armor",query("armor_prop/armor",  ob2), ob);
        set("max_enchant",query("max_enchant",  ob2), ob);
        set("base_armor",query("armor_prop/armor",  ob2), ob);
        ob->save();
        ob->restore();
        if(ob->move(me)){
        gold->add_amount(-1);
        addn("created_item", 1, me);
        me->start_busy(1);
        write("你将身上的"+ob2->name()+"交给"+name()+"，打造成一"+query("unit", ob)+
        ob->name()+"\n");
        destruct(ob2);
        seteuid(getuid());
        return 1;
        }
        return 0;
}
int check_legal_name(string name)
{
        int i;
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 40 ) ) {
                write("对不起，中文名字必须是一到二十个中文字。\n");
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
