// /adm/daemons/paiming_d.c
// by Find.

/*********************************************
 * 每日凌晨三点自动刷新,此时机器负担应该很轻.
 * 此程序运行的负担应该很轻,如要再减低负担可将
 * USER_PER_CALL 的数字减小,但会增加此程序的运
 * 行时间.如感觉没什么负担想提升执行速度,可适当
 * 将这个数字增加.
 *********************************************/

// #pragma optimize

#define MIN_FORCE	1000
#define MIN_GOLD	100
#define MIN_EXP		100000	// 参加排名的最低要求经验值.
#define USER_PER_CALL	10
#define YIJIA_ROOM	"/d/changan/ly-ge3"
#define ERJIA_ROOM	"/d/changan/ly-ge2"

#include <ansi.h>

inherit F_SAVE;

class player_data
{
	string id;
	string name;
	string title;
	int exp;
	int gold;
	int force;
}

protected class player_data *top_exp = ({});
protected class player_data *top_rich = ({});
protected class player_data *top_force = ({});

protected nosave int top_number = 10;

protected void init_dirs_and_args();
protected void begain_sort();
protected void update_top_room();
protected void add_to_top_exp(object);
protected void add_to_top_rich(object);
protected void add_to_top_force(object);
protected void refresh_room(string);

protected nosave int is_sorting = 0;

protected nosave string *dirs = ({}), *second_dir = ({});
protected nosave int dpos,upos;

protected string make_news();

int query_is_sorting() { return is_sorting; }
string query_save_file() { return DATA_DIR+"paiming_d"; }

protected void create()
{
	seteuid(getuid());
	restore();
}

nomask void main()
{
	if( !previous_object() || (geteuid(previous_object()) != ROOT_UID ))
		return;

	if(is_sorting)
		return;
	is_sorting = 1;
	seteuid(ROOT_UID);

	init_dirs_and_args();
	return;
}

protected void init_dirs_and_args()
{
	string *temp_dir,str;
	int i;

	top_exp = ({});
	top_rich = ({});
	top_force = ({});
	dirs = ({});

	temp_dir = get_dir(DATA_DIR+"user/");

	for(i=0;i<sizeof(temp_dir);i++)
	{
		if(file_size(str = DATA_DIR+"user/"+temp_dir[i]) != -2)
			continue;
		else
			dirs += ({ str+"/" });
	}

	dpos = 0;

	second_dir = get_dir(dirs[dpos]);
	upos = 0;

	begain_sort();
	return;
}

protected void begain_sort()
{
	string pid;
	int i = USER_PER_CALL;
	object login,user;

	remove_call_out("begain_sort");

	if(upos >= sizeof(second_dir))
	{
		dpos++;
		if(dpos >= sizeof(dirs))
		{
			save();
			update_top_room();
			return;
		}
		else
		{
			second_dir = get_dir(dirs[dpos]);
			upos = 0;
		}
	}

	while(i--)
	{
		if(upos >= sizeof(second_dir))
			break;
		reset_eval_cost();
		if( !sscanf(second_dir[upos], "%s.o", pid) )
		{
			upos++;
			continue;
		}

		if( (string)SECURITY_D->get_status(pid) != "(player)" )
		{
			upos++;
			continue;
		}

		login = new(LOGIN_OB);
		login->set("id",pid);
		if( !login->restore() )
		{
			destruct(login);
			log_file("pai_err","can't restore "+pid+"'s login_ob.\n");
			upos++;
			continue;
		}
		if(!objectp(user = LOGIN_D->make_body(login)))
		{
			destruct(login);
			log_file("pai_err","can't make "+pid+"'s body.\n");
			upos++;
			continue;
		}
		if( !user->restore() )
		{
			destruct(login);
			destruct(user);
			log_file("pai_err","can't restore "+pid+"'s user_ob.\n");
			upos++;
			continue;
		}

		add_to_top_exp(user);
		add_to_top_rich(user);
		add_to_top_force(user);

		destruct(user);
		destruct(login);
		upos++;
	}

	call_out("begain_sort",3);
	return;
}

protected int sort_top_exp(class player_data t1, class player_data t2)
{
	if(t1->exp > t2->exp)
		return -1;
	return 1;
}

protected void add_to_top_exp(object ply)
{
	class player_data tmp;
	int exp;

	if(!objectp(ply))
		return;

	if( (exp = ply->query("combat_exp")) < MIN_EXP )
		return;

	if(sizeof(top_exp) < top_number)
	{
		if(!top_exp || !sizeof(top_exp))
			top_exp = ({});

		tmp = new(class player_data);
		tmp->id = ply->query("id");
		tmp->name = ply->name();
		tmp->title = ply->query("title");
		tmp->exp = exp;
		top_exp += ({ tmp });
		top_exp = sort_array(top_exp, (: sort_top_exp :));
		return;
	}

	if( exp > top_exp[top_number -1 ]->exp)
	{
		tmp = new(class player_data);
		tmp->id = ply->query("id");
		tmp->name = ply->name();
		tmp->title = ply->query("title");
		tmp->exp = exp;
		top_exp[top_number-1] = tmp;
		top_exp = sort_array(top_exp, (: sort_top_exp :));
		return;
	}
}

protected void update_top_room()
{
	string news;

	refresh_room(YIJIA_ROOM);
	refresh_room(ERJIA_ROOM);

	log_file("paiming",sprintf("江湖排名结果:\n%O\n", top_exp));

	news = make_news();
	NEWS_D->add_news_item( news , "p", 1);
	is_sorting = 0;
}

protected void refresh_room(string file)
{
	string err;
	object *inv, room;
	int i;

	if(!stringp(file) || !sizeof(file))
		return;

	if(!room = find_object(file))
		return;

	inv = all_inventory(room);

	if(i = sizeof(inv))
	{
		while(i--)
		{
			if(inv[i]->is_character())
				inv[i]->move(VOID_OB, 1);
			else
				inv[i] = 0;
		}
	}

	inv -= ({ 0 });

	destruct(room);

	if(room)
		return;

	if(err = catch( call_other(file, "???") ))
		return;

	if(!room = find_object(file))
		return;

	if(i=sizeof(inv))
	{
		while(i--)
		{
			if(inv[i] && inv[i]->is_character())
				inv[i]->move(room, 1);
		}
	}
}

protected string make_msg(class player_data *big_players, string name)
{
	int len,i,n;
	string head,content="",end,bk="";

	if(!(n=sizeof(big_players)))
		return "";

	foreach(class player_data tmp in big_players)
	{
		int l = strlen(tmp->title) + strlen(tmp->name) + strlen(tmp->id) + 3;
		if(len < l)
			len = l;
	}

	len += 4;
	if(len%2)
		len++;

	head = sprintf(HIY"\n%|"+(string)len+"s\n%|"+(string)len+"s\n╔",sprintf("〖 天下%s榜 〗",name),"☉☉☉☉☉☉☉☉☉☉☉☉☉");

	bk = repeat_string("═", len/2);
	head += sprintf("%s╗\n",bk);
	end =  sprintf("╚%s╝%s\n",bk,NOR);

	for(i=0;i<n;i++)
	{
		content += sprintf("║%|"+(string)len+"s║\n",sprintf("%s %s(%s)",
			big_players[i]->title, big_players[i]->name, capitalize(big_players[i]->id) ));
		if(i == (n-1))
			content += end;
		else
			content += sprintf("╠%s╣\n",bk);
	}

	return (head + content);
}

protected void make_renyi_bang()
{
	mixed *bang;
	string bang_file, out = HIY"
                《仁义山庄》悬赏榜\n\n";

	bang = DATABASE_D->db_query_bang_top_ten();

	bang_file = MISC_DIR"top_bang";

	if(sizeof(bang))
		foreach(mixed *tmp in bang)
			out += sprintf("悬赏追杀：%s(%s)
    %-22s  当前赏金：%d 两黄金\n\n", tmp[1], tmp[0],
		sizeof(tmp[2])?sprintf("曾在%s学艺",tmp[2]):"师承门派未能查清",tmp[3]);

	out += (string)NOR;

	write_file(bang_file, out, 1);
}

protected string make_news()
{
	string out;

	out = make_msg(top_rich, "财富");
	write_file(MISC_DIR"top_rich",out,1);

	out = make_msg(top_force, "内功");
	write_file(MISC_DIR"top_force",out,1);

	out = make_msg(top_exp, "金");
	write_file(MISC_DIR"top_exp",out,1);

	write_file("/paiming", implode(explode(clr_ansi(out),"\n")-({""}),"<br>"), 1);
	make_renyi_bang();
	return (out);
}

int query_player_data(int num, string ref name, string ref id, string ref title
/*, int ref exp, int ref male, int ref age*/)
{
	if(!intp(num) || (num < 1) || (num > sizeof(top_exp)))
		return 0;

	num--;

	name = top_exp[num]->name;
	id = top_exp[num]->id;
	title = top_exp[num]->title;
	//exp = top_exp[num]->exp;
	//male = top_exp[num]->male;
	//age = top_exp[num]->age;

	return 1;
}

// 先这样凑合着
protected int sort_top_rich(class player_data t1, class player_data t2)
{
	if(t1->gold > t2->gold)
		return -1;
	return 1;
}

protected void add_to_top_rich(object ply)
{
	class player_data tmp;
	mapping bank;
	int gold;

	if(!objectp(ply) || !mapp(bank = ply->query("save_in_bank")) || !sizeof(bank))
		return;

	gold = bank["gold"] + bank["silver"]/100 + bank["coin"]/10000;
	if(gold < MIN_GOLD)
		return;

	if(sizeof(top_rich) < top_number)
	{
		if(!top_rich || !sizeof(top_rich))
			top_rich = ({});

		tmp = new(class player_data);
		tmp->id = ply->query("id");
		tmp->name = ply->name();
		tmp->title = ply->query("title");
		tmp->gold = gold;
		top_rich += ({ tmp });
		top_rich = sort_array(top_rich, (: sort_top_rich :));
		return;
	}

	if( gold > top_rich[top_number -1 ]->gold)
	{
		tmp = new(class player_data);
		tmp->id = ply->query("id");
		tmp->name = ply->name();
		tmp->title = ply->query("title");
		tmp->gold = gold;
		top_rich[top_number-1] = tmp;
		top_rich = sort_array(top_rich, (: sort_top_rich :));
		return;
	}
}

protected int sort_top_force(class player_data t1, class player_data t2)
{
	if(t1->force > t2->force)
		return -1;
	return 1;
}

protected void add_to_top_force(object ply)
{
	class player_data tmp;
	int force;

	if(!objectp(ply))
		return;

	if((force = ply->query("max_force")) < MIN_FORCE)
		return;

	if(sizeof(top_force) < top_number)
	{
		if(!top_force || !sizeof(top_force))
			top_force = ({});

		tmp = new(class player_data);
		tmp->id = ply->query("id");
		tmp->name = ply->name();
		tmp->title = ply->query("title");
		tmp->force = force;
		top_force += ({ tmp });
		top_force = sort_array(top_force, (: sort_top_force :));
		return;
	}

	if( force > top_force[top_number -1 ]->force)
	{
		tmp = new(class player_data);
		tmp->id = ply->query("id");
		tmp->name = ply->name();
		tmp->title = ply->query("title");
		tmp->force = force;
		top_force[top_number-1] = tmp;
		top_force = sort_array(top_force, (: sort_top_force :));
		return;
	}
}
