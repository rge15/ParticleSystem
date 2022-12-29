#pragma once
#include <utilities/alias.hpp>
#include <iostream>
#include <assert.h>
#include <Engine/utils/metaProggraming.hpp>

//Structure for Index data
struct IdPair
{
	Size_t _id{ 0 };
	int _gen {-1};
};

template<typename... T>
class Slotmap
{
	using Indices = Vector<IdPair>;
	using VectorTypes = Tuple<T...>;
	using Data = Tuple< Vector<T>... >;
	using FType = std::tuple_element_t<0, std::tuple<T...>>;

	private:
		//Slot Generation Counter
		int _genCtr { 0 };
		//Free slot id
		Size_t _free { 0 };
		//Vector of Slot Indices
		Indices _index {};
		//Tuple of vectors with data contiguous in memory
		Data _data {};
		Size_t _numAttributes = std::tuple_size<Data>{};
		//Vector of id's to _index Slot that contains de _data;
		Vector<Size_t> _clear {};

	    static constexpr auto reserveVectorData = [](int val, auto&& tuple_value)
	    {
	        //std::cout << "Vec data capacity : " << tuple_value.capacity() << '\n';
	        //std::cout << "Size to reserve : " << val << '\n';
	        tuple_value.reserve(val);
	        //std::cout << "Vec data capacity : " << tuple_value.capacity() << '\n';
	    };

	    static constexpr auto addVectorData = [](auto&& tuple_value)
	    {
	        tuple_value.emplace_back();
	    };

	    static constexpr auto removeVectorData = [](int pos, auto&& tuple_value)
	    {
			tuple_value[ pos ] = std::move( tuple_value.back() );
	    };

	    static constexpr auto popVectorData = [](auto&& tuple_value)
	    {
			tuple_value.pop_back();
	    };

		/**
		 * 	@brief Resizes the index, data & clearIndex containers
		*/
		void
		resize() noexcept;

		/**
		 * 	@brief Given a data reference returns his position in the slotmap data array. If not founded returns -1
		 * 
		 * 	@param p_data REference to data to find his position
		*/
		Size_t
		getDataId( const FType& p_data ) const noexcept;

		/**
		 * 	@brief Reserves a free Slot Index position in the index array and fill his rata
		 * 
		 * 	@param p_val Reference to data object in slotmap data. Is used for setting the 
		 * Slot ID relative to his position in the Slotmap data vector.
		 * 	
		 * 	@return Returns the Slot position at the slotmap _index vector.
		*/
		Size_t
		getSlotID( const FType& p_val ) noexcept;

		/**
		 * 	@brief Checks if the slotmap needs to be resized
		*/
		void
		checkSize() noexcept;

		/**
		 * 	@brief Renums the index contained at the empty slots
		*/
		void
		renumIndexChain() noexcept;

		void
		reserveData(int p_size) noexcept;

	public:
		/**
		 * 	@brief Constructor of Slotmap Class
		 * 
		 * 	@param p_size Initial Size of the slotmap data container
		*/
		Slotmap( Size_t p_size = 10 ) noexcept;

		// Default destructor of SlotmapClass
		//~Slotmap() = default;
		~Slotmap(){
			std::cout << "Total particles in this : " << std::get<0>(_data).size() << "\n";
		}
		
		/**
		 * 	@brief Adds data to the slotmap
		 * 
		 * 	@param p_data Object to add into the Slotmap data
		 * 
		 * 	@return Returns the key for acces with the inserted data
		*/
		IdPair
		addSlot() noexcept;

		/**
		 * 	@brief Delets the data given his key
		 * 
		 * 	@param p_slot Key of the element to delete
		*/
		void
		deleteSlot( const IdPair& p_slot ) noexcept;

		/**
		 * 	@brief Gets the object reference given the key
		 * 
		 * 	@param p_slot Key of the object reference to get
		 * 
		 * 	@return Reference to the object.
		*/
		template<typename t>
		t&
		getItem( const IdPair& p_slot ) noexcept;

		/**
		 * 	@brief Gets a reference to the data vector
		 * 
		 * 	@return Reference to the data vector
		*/
		Data&
		getDataVector() noexcept { return _data; };

		Vector<Size_t>&
		getClearVector() noexcept { return _clear; };

		template<typename t>
		Vector<t>&
		getDataVector() noexcept;

		void
		autoDeleteSlot( const int p_pairId ) noexcept;

};

#include "Slotmap.tpp"