
template<typename... T>
Slotmap<T...>::Slotmap( Size_t p_size ) noexcept
{

	reserveData(p_size);

	_clear.reserve(p_size);

	_index.resize(p_size);
	
	renumIndexChain();

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
void
Slotmap<T...>::resize() noexcept
{
	Size_t newSize = _clear.capacity() * 2;

	reserveData( newSize );

	_clear.reserve( newSize );

	_index.resize( newSize );

	renumIndexChain();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
void
Slotmap<T...>::reserveData(int p_size) noexcept
{
	std::apply([&](auto&&... vector){
		(Slotmap::reserveVectorData(p_size, vector),...);
	},_data);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
void
Slotmap<T...>::renumIndexChain() noexcept
{
	int i = _free;
	for(auto& pair : _index)
		if(pair._gen == -1)
			pair._id = ++i;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
Size_t
Slotmap<T...>::getDataId( const FType& p_data ) const noexcept
{
	Size_t ctr { 0 };

	auto& vec = std::get<0>(_data);

	for(auto& value : vec)
	{
		if( &value == &p_data)
			return ctr;
		++ctr;
	}

	return -1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
void
Slotmap<T...>::checkSize() noexcept
{
	auto dataCapacity = _clear.capacity();

	if( dataCapacity == _clear.size() )
		resize();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
IdPair
Slotmap<T...>::addSlot() noexcept
{
	checkSize();

	//TODO [Check] : Aquí añadir a todos los vectors de data un emplaceback
	std::apply([&](auto&&... p_vector)
	{
		( Slotmap::addVectorData(p_vector),... );
	},_data);

	_clear.emplace_back( _free );

	auto& vec1 = std::get<0>(_data);
	auto& val = vec1.back();

	//TODO [Check] : Del primer vector si que hay que pasar la referencia
	Size_t keyUser = getSlotID( val );

	return { keyUser , _genCtr++ };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//TODO : Esto será unicamente para el primer type de la tupla pero funciona igual
template<typename... T>
Size_t
Slotmap<T...>::getSlotID( const FType& p_val ) noexcept
{
	auto& idPair = _index[_free];
	Size_t userKey = _free;
	_free = idPair._id;
	idPair._gen = _genCtr;
	idPair._id = getDataId( p_val );

	return userKey;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//TODO : Aquí toca borrar y mover una vez por cada tipo en la tupla
template<typename... T>
void
Slotmap<T...>::deleteSlot( const IdPair& p_pair ) noexcept
{
	auto& indexToErase = _index.at(p_pair._id);
	//1º : Checkear que el indice sea valido
	if( indexToErase._gen != p_pair._gen )
	{
		std::cout << "Trying to delete with invalid key \n";
		return;
	}

	//2º : Guardamos el _index[p_pair._id]._id en dataToErase
	Size_t dataToErase = indexToErase._id;

	//3º : Pasar el p_pair._id a _free y el _free al _index[p_pair._id]._id
	indexToErase._id = _free;
	_free = p_pair._id;

	//4º : Pasar el _index[p_pair._id]._gen a -1
	indexToErase._gen = -1;

	//5º : Pasamos el último de _data y el último de _clear a _data[dataToErase] y _clear[dataToErase]
	std::apply([&](auto&&... vector){
		(removeVectorData(dataToErase, vector),...);
	}, _data);
	//_data[ dataToErase ] = std::move( _data.back() );
	_clear[ dataToErase ] = std::move( _clear.back() );
	
	//6º Eliminamos los ultimos datos ya movidos
	std::apply([&](auto&&... vector){
		(popVectorData(vector),...);
	}, _data);
	//_data.pop_back();
	_clear.pop_back();

	//7º : Una vez pasado los datos, con el _clear[dataToErase] cambiamos el _indices[_clear[dataToErase]] a dataToErase
	_index.at( _clear[ dataToErase ] )._id = dataToErase;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename... T>
void
Slotmap<T...>::autoDeleteSlot( const int p_pairId ) noexcept
{
	auto& indexToErase = _index.at(p_pairId);
	//1º : Checkear que el indice sea valido
	//if( indexToErase._gen != p_pair._gen )
	//{
	//	std::cout << "Trying to delete with invalid key \n";
	//	return;
	//}

	//2º : Guardamos el _index[p_pair._id]._id en dataToErase
	Size_t dataToErase = indexToErase._id;

	//3º : Pasar el p_pair._id a _free y el _free al _index[p_pair._id]._id
	indexToErase._id = _free;
	_free = p_pairId;

	//4º : Pasar el _index[p_pair._id]._gen a -1
	indexToErase._gen = -1;

	//5º : Pasamos el último de _data y el último de _clear a _data[dataToErase] y _clear[dataToErase]
	std::apply([&](auto&&... vector){
		(removeVectorData(dataToErase, vector),...);
	}, _data);
	//_data[ dataToErase ] = std::move( _data.back() );
	_clear[ dataToErase ] = std::move( _clear.back() );
	
	//6º Eliminamos los ultimos datos ya movidos
	std::apply([&](auto&&... vector){
		(popVectorData(vector),...);
	}, _data);
	//_data.pop_back();
	_clear.pop_back();

	//7º : Una vez pasado los datos, con el _clear[dataToErase] cambiamos el _indices[_clear[dataToErase]] a dataToErase
	_index.at( _clear[ dataToErase ] )._id = dataToErase;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//TODO : Esto habrá que pasar otro template para pedir el dato que queremos
template<typename... T>
template<typename t>
t&
Slotmap<T...>::getItem( const IdPair& p_slot ) noexcept
{
	// TODO : Check if exists
	static_assert( MP::has_type<t, VectorTypes>() , "Slotmap Doesn't contain that type");

	auto& indexPair = _index.at(p_slot._id);

	if( indexPair._gen != p_slot._gen )
	{
		std::cout << "Trying to get Item with invalid key \n";
		assert(false);
	}

	auto& vec = std::get<Vector<t>>(_data);

	return vec[indexPair._id];
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// TODO : Hacer un getData que devuelva el array con los datos del type especificado en la template
template<typename... T>
template<typename t>
Vector<t>&
Slotmap<T...>::getDataVector() noexcept
{
	// TODO : Check if exists
	static_assert( MP::has_type<t, VectorTypes>() , "Slotmap Doesn't contain that type");

	auto& vec = std::get<Vector<t>>(_data); 

	return vec;
}
