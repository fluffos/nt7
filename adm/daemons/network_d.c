/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : network_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2002-9-12
 * Note   : 网路资讯精灵
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <daemon.h>

nomask string query_network_short(object user)
{
	string network_short;
	mapping login;
	
	if( !objectp(user) )
		return 0;

	login = query_temp("login", user);
	
	if( !mapp(login) ) login = allocate_mapping(0);
	
	network_short = sprintf("<%s/%s/%s/%s/%s/%s>",
		capitalize(SECURE_D->level_name(user->query_id(1))),
		query_ip_number(user)||login["ip"]||"-",
		query_ip_name(user)||login["ip_name"]||"-",
		(query_ip_port(user)||login["ip_port"]||"-")+"",
		login["terminaltype"]||"-",
		login["ident"]||"-",
		);

	network_short = replace_string(network_short, "\n", "");
	return network_short;
}

string dsize(int size)
{
	if( size < 1024 )
		return size + " Bytes";
	
	if( size < 1048576 )
		return sprintf("%.3f KBytes", size / 1024.);
		
	if( size < 1073741824 )
		return sprintf("%.3f MBytes", size / 1048576.);

	if( size < 1099511627776 )
		return sprintf("%.3f GBytes", size / 1073741824.);

	if( size < 1125899906842624 )
		return sprintf("%.3f TBytes", size / 1099511627776.);
}

string query_network_packet_stats()
{
	mapping networkstats = network_stats();

	return sprintf("已接收 %s 封包(%.2f/sec)，已传送 %s 封包(%.2f/sec)", NUMBER_D->number_symbol(networkstats["incoming packets total"]), to_float(networkstats["incoming packets total"])/uptime(), NUMBER_D->number_symbol(networkstats["outgoing packets total"]), to_float(networkstats["outgoing packets total"])/uptime());

}

string query_network_volume_stats()
{
	mapping networkstats = network_stats();

	return sprintf("已接收 %s 资料(%.3f KBytes/sec)，已传送 %s 资料(%.3f KBytes/sec)", dsize(networkstats["incoming volume total"]), to_float(networkstats["incoming volume total"])/1024./uptime(), dsize(networkstats["outgoing volume total"]), to_float(networkstats["outgoing volume total"])/1024./uptime());

}

void create()
{

}
string query_name()
{
	return "网路资讯系统(NETWORK_D)";
}
