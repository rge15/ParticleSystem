
template<typename T>
Slotmap<T>::Slotmap( Size_t p_size ) noexcept
{
	_data.reserve(p_size);
	_clear.reserve(p_size);

	_index.resize(p_size);
	
	renumIndexChain();

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
void
Slotmap<T>::resize() noexcept
{
	Size_t newSize = _data.capacity() * 2;

	_data.reserve( newSize );
	_clear.reserve( newSize );

	_index.resize( newSize );

	renumIndexChain();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
void
Slotmap<T>::renumIndexChain() noexcept
{
	int i = _free;
	for(auto& pair : _index)
		if(pair._gen == -1)
			pair._id = ++i;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
Size_t
Slotmap<T>::getDataId( const T& p_data ) const noexcept
{
	Size_t ctr { 0 };

	for(auto& value : _data)
	{
		if( &value == &p_data)
			return ctr;
		++ctr;
	}

	return -1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
void
Slotmap<T>::checkSize() noexcept
{
	auto dataCapacity = _data.capacity();

	if( dataCapacity == _data.size() )
		resize();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
IdPair
Slotmap<T>::addSlot(T& p_data) noexcept
{
	checkSize();

	auto& val = _data.emplace_back( std::move(p_data) );

	_clear.emplace_back( _free );

	Size_t keyUser = getSlotID( val );

	return { keyUser , _genCtr++ };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
IdPair
Slotmap<T>::addSlot(T&& p_data) noexcept
{
	checkSize();

	auto& val = _data.emplace_back( p_data );

	_clear.emplace_back( _free );

	Size_t keyUser = getSlotID( val );

	return { keyUser , _genCtr++ };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<typename T>
Size_t
Slotmap<T>::getSlotID( const T& p_val ) noexcept
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

template<typename T>
void
Slotmap<T>::deleteSlot( const IdPair& p_pair ) noexcept
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
	_data[ dataToErase ] = std::move( _data.back() );
	_clear[ dataToErase ] = std::move( _clear.back() );
	
	//6º Eliminamos los ultimos datos ya movidos
	_data.pop_back();
	_clear.pop_back();

	//7º : Una vez pasado los datos, con el _clear[dataToErase] cambiamos el _indices[_clear[dataToErase]] a dataToErase
	_index.at( _clear[ dataToErase ] )._id = dataToErase;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


template<typename T>
T&
Slotmap<T>::getItem( const IdPair& p_slot ) noexcept
{
	auto& indexPair = _index.at(p_slot._id);

	if( indexPair._gen != p_slot._gen )
	{
		std::cout << "Trying to get Item with invalid key \n";
		assert(false);
	}

	return _data[indexPair._id];
}
