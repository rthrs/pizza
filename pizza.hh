#ifndef __PIZZA_HH__
#define __PIZZA_HH__

#include <cstddef>
#include <type_traits>
#include <array>
#include <iostream>

template<typename... Kinds> struct Pizzeria {

private:

   static constexpr size_t default_slices_count = 8;

   template<typename Kind, typename... Menu> static constexpr size_t count_kind() {
      return (std::is_same<Kind, Menu>::value + ...);
   }
 
   static constexpr bool check_duplicates() {
      return ((count_kind<Kinds, Kinds ...>() == 1) && ...);
   }

   template<size_t... Slices> struct Pizza {

   private:
      
      using pizzeria = Pizzeria<Kinds ...>;

   public:

      template<typename Kind> static constexpr size_t count() {
         return ((std::is_same<Kind, Kinds>::value ? Slices : 0) + ...);
      }   

      static constexpr std::array<size_t, sizeof... (Slices)> as_array() {
         return std::array<size_t, sizeof... (Slices)> {{Slices ...}};
      }

      using sliced_type = Pizza<(Slices * 2) ...>;

   };

public:

/*
    static constexpr std::array<bool, sizeof... (Kinds)> lol() {
         return std::array<bool, sizeof... (Kinds)> {{(count_kind<Kinds, Kinds ...>() == 1) ...}};
   }
*/

  static_assert(check_duplicates(), "Duplicated pizzas!");

  template<typename Kind> struct make_pizza {
      static_assert(count_kind<Kind, Kinds ...>() == 1, "There is no such a pizza name in menu!");
      using type = Pizza<(std::is_same<Kind, Kinds>::value ? default_slices_count : 0) ...>;
   };

};
/*
template <typename Pizza> int maxi_pizza(int slices) {
	long long total = 0;
	int size = 0;		
	for(int i = 0; i < slices; i++) {
		long long acc = Pizza.yummines(i);
		if(acc > total) {
			total = acc;
			size = i;
		}
	}
	return size;
}

template<typename Pizza1, typename Pizza2> struct best_mix {
	using connected = {};// tutaj trzeba pizze1 i pizze2 połaczyć w jedna
	using type = Pizza<(maxi_pizza<Kinds>(Slices)) ... >//iterujemy po rodzajach i ilościach kawakłów (kod raczej niepoprawny)
};*/

#endif /* __PIZZA_HH__ */
