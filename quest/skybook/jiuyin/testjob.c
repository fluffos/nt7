// houdian.c 后殿

inherit ROOM;
void create()
{
	set("short", "后殿");
	set("long",@long
这是峨嵋山华藏庵的后殿。是峨嵋派掌门人传教弟子功夫的地方。这里供
有一尊普贤菩萨像。两旁靠墙放着几张太师椅，地上放着几个蒲团。掌门人正
在向几个女弟子传授武功。
long);
	set("exits",([
		"north" : __DIR__"daxiong",
	]));
        set("objects",([
//                CLASS_D("emei") + "/mie-jue" : 1,
	]));
//	create_door("north", "小门", "south", DOOR_CLOSED);
        setup();
}

void reset()
{
	object here=this_object();
	if (here->query("fighting") != 1) {
		if (here->query("count") != 1)
			here->set("count", random(4) );
		if ((int)here->query("count") == 1){
			remove_call_out("test");
			call_out("test", 5, here);
		}
	}
	::reset();
}

int sort(object obj1, object obj2)
{
	int temp1,temp2;
	temp1 = obj1->query("em_job1");
	temp2 = obj2->query("em_job1");
	if (temp1 > temp2) return 1;
	else if (temp1 < temp2) return -1;
	else return 0;
}

void test(object here)
{
	string s;
	object ob, ling, where;
	object *list, *selected, *sorted;
	int num0, num1, num2, num3;
	int i, cnt = 0;
	string* tgt= ({ "/d/emei/houshanty", "/d/emei/baoguosi", "/d/emei/sheshenya",
                        "/d/emei/zhongfengsi", "/d/emei/qianfoan", "/d/emei/chunyangdian",
                        "/d/emei/guanyinqiao", "/d/emei/jietuopo", "/d/emei/xianfengsi" });
	string* tgtname= ({ "炭窑", "报国寺", "舍身崖", "中峰寺", "千佛庵",
                            "纯阳殿", "观音桥", "解脱坡", "仙峰寺"});
	num0 = -1;
	num2 = -1;
	num3 = -1;
	num1 = -1;
	num0 = random(sizeof(tgt));
	num1 = random(sizeof(tgt));
	while (num0 == num1) {
		num1 = random(sizeof(tgt));
	}
	num2 = random(sizeof(tgt));
	while (num0 == num2 || num1 == num2) {
		num2 = random(sizeof(tgt));
	}
	num3 = random(sizeof(tgt));
	while (num0 == num3 || num1 == num3 || num2 == num3) {
		num3 = random(sizeof(tgt));
	}
	if (!(ob = present("miejue shitai", here))) return;
	list = filter_array(users(), (: $1->query_temp("emhsjob"):));
	sorted = sort_array(list, (: sort :));
	i = sizeof( sorted );
	while( i-- ) {
		if (!environment(list[i]) ) continue;
		if (wizardp(list[i]) || list[i]->query("env/invisibility")) continue;
		if ( !interactive(list[i]) ) continue;
		if (query_idle(list[i]) > 2000) continue;
		cnt++;
		list[i]->set_temp("selected", 1);
	}
	if ( cnt < 2 ) {
		here->set("count", random(2));
		return;
	}
	selected = filter_array(list, (: $1->query_temp("selected") == 1 :));
	i = 1;
	if (!(where = find_object("fang ping")))
		ling = new("/d/emei/npc/fang");
	else ling = present("fang ping", where);
	ling->move("/d/city/yltw");
	ling->set("pl", selected[0]);
	s = selected[0]->query("name")+"赶紧到扬州月老亭把方老前辈请来助阵，";
	while( i < 5 ) { ling->set("pl"+i, ling); i++; }
	ling->set("pl1",selected[1]);
	ling->set("st1",tgt[num0]);
	s = s + selected[1]->query("name")+"守住"+tgtname[num0]+"，";
	if( cnt > 2 ) {
		ling->set("pl2",selected[2]);
		ling->set("st2",tgt[num1]);
		s = s + selected[2]->query("name")+"守住"+tgtname[num1]+"，";
	}
	if( cnt > 3 ) {
		ling->set("pl3",selected[3]);
		ling->set("st3",tgt[num2]);
		s = s + selected[3]->query("name")+"守住"+tgtname[num2]+"，";
	}
	if( cnt > 4 ) {
		ling->set("pl4",selected[4]);
		ling->set("st4",tgt[num3]);
		s = s + selected[4]->query("name")+"守住"+tgtname[num3]+"，";
	}
	CHANNEL_D->do_channel(ob, "chat", "元兵攻山，" + s + "等待援兵，杀退敌人！\n");
	ling->apply_condition("em_job1", 30);
	ling->apply_condition("job_busy", 30);
	here->set("fighting", 1);
	return;
}

void init()
{
	add_action("do_swear",  ({ "qishi", "fashi" }));
	add_action("do_huzhuo",  ({ "huzhuo" }));
	add_action("do_nod",  ({ "nod" }));
}

int do_swear()
{
	object ob, me = this_player();
	object where = environment(me);
	if( !(ob = present("miejue shitai", where) ) )
		return 0;
	if( me->query_temp("jiuyin140") < 5 )
		return 0;
	if( me->query("gender") == "女性" )
		message_vision("$N说道：小女子" + me->query("name") + "对天盟誓，日后我若对魔教教主张无忌这淫徒心存爱慕，\n"+
			"倘若和他结成夫妇，我亲身父母死在地下，尸骨不得安稳；我师父灭绝师太必成厉鬼，\n"+
			"令我一生日夜不安，我若和他生下儿女，男子代代为奴，女子世世为娼。\n", me);
	else
		tell_room(where, me->query("name")+"说道：不才" + me->query("name") + "一定要实现师太的两大愿望，逐走鞑子，\n"+
			"光复汉家山河；率领峨嵋派领袖群伦，盖过少林、武当，成为中原武林中的第一门派。\n"+
			"有违誓言者天打雷劈，万剑穿身，死无葬身之地。\n");
	tell_room(where, "灭绝师太脸上露出一丝笑容。\n");
	me->set_temp("jiuyin140", 6);
	tell_room(where, "灭绝师太说道：黄女侠在铸刀铸剑之前，和郭大侠两人穷一月心力，缮写了兵法和武功的\n"+
			"精要，分别藏在刀剑之中。屠龙刀中藏的乃是兵法，此刀名为‘屠龙’，意为日后有人得\n"+
			"到刀中兵书，当可驱除鞑子，杀了鞑子皇帝。倚天剑中藏的则是武学秘笈，其中最为宝贵\n"+
			"的，乃是一部‘九阴真经’，一部‘降龙十八掌掌法精义’，盼望后人习得剑中武功，替\n"+
			"天行道，为民除害。\n");
	tell_room(where, "灭绝师太说道：你取到屠龙刀和倚天剑后，来到我这里，一手执刀，一手持剑，运起内力，\n"+
			"以刀剑互斫(huzhuo)，宝刀宝剑便即同时断折，即可取出藏在刀身和剑刃中的秘笈。这是\n"+
			"取出秘笈的唯一法门，那宝刀宝剑可也从此毁了。你记住了么？\n");
	return 1;
}

int do_nod()
{
	object me=this_player();
	if( me->query_temp("jiuyin140") != 6 ) return 0;
	me->set_temp("jiuyin140", 7);
	message_vision("$N只听得浑身热血沸腾，一股浩然的正气充满胸襟。\n", me);
	me->add("shen", me->query("combat_exp")/3);
	return 0;
}

int do_huzhuo()
{
	object ob, me=this_player();
	object ob1, ob2, where = environment(me);
	if( me->query_temp("jiuyin140") < 6 ) return 0;
	if( !(ob1 = present("yitian jian", me)) ) return 0;
	if( !(ob2 = present("tulong dao", me)) ) return 0;
	if( me->query_temp("jiuyin140") != 7 )
		return notify_fail("你答应了灭绝师太的要求了吗？\n");
	if ( !me->query("jiuyin/emeipass") || !me->query("jiuyin/emeijump"))
		return notify_fail("嘿嘿！想作弊么？\n");
	if( !(ob = present("miejue shitai", where) ) )
		return notify_fail("灭绝师太不在这里，你最好先别这样做。\n");
	message_vision("只见$N一手执刀，一手持剑，运起内力，刀剑互斫。\n"+
			"只听见‘哧’的一声轻响，这两把举世无双的屠龙刀和倚天剑就此消失了。\n", me);
	destruct(ob1);
	destruct(ob2);
	message_vision("灭绝师太从断刀断剑中取出了几张帛卷，看了几眼，拿出一张帛卷交给了$N。\n", me);
	if( me->query_skill("xianglong-zhang", 1) > 0)
	        tell_room(where, "灭绝师太说道：降龙十八掌你已经学了，这张九阴白骨爪精解你就拿去学吧。\n");
	else
		tell_room(where, "灭绝师太说道：你的武学路子与降龙十八掌的刚阳劲力不符，这张九阴白骨爪精解你就拿去学吧。\n");
	tell_room(where, "灭绝师太说道：待我觅得一个心地仁善、赤诚为国的志士，将兵书传授于他，要他立誓驱除胡虏。\n");
	tell_room(where, "灭绝师太又说道：我看这还是我先保管，你如果需要随时来跟我要吧。\n");
	me->set("jiuyin/emei",1);
	log_file("quest/jiuyin",sprintf("%-18s在娥眉九阴部分失败%s次后成功从灭绝师太处得到娥眉九阴。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("jiuyin/emeifail"))), me);
	me->delete_temp("jiuyin140");
	return 1;
}
